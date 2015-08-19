#include "webdispatch.h"
#include <QFile>
#include <QDirIterator>

#include "assist.h"

#define __CLASS__ "~WebDispatch~"

void WebDispatch::__process_websources()
{
    emit signal_SourceHandleStarted();
    __debug_p( "Rebuilding avaliable hosts..." );

    QDirIterator it( ":/web_path", QDirIterator::Subdirectories );

    qmap.clear();

    while( it.hasNext() )
    {
        QString fn = it.next();
        QFile f( fn );
        if( ! f.open(QIODevice::ReadOnly) )
        {
            __debug_p( "Cannot open " << fn << "." );
            continue;
        }

        QTextStream in( &f );
        QStringList l;
        while( ! in.atEnd() )
        {
            QString line = in.readLine();
            if( ! line.isEmpty() )
            {
                l << line;
                connections_fired++;
                qnet->get( QNetworkRequest( QUrl( line ) ) );
            }
        }
        qmap.insert( QFileInfo( fn ).baseName() , l );
        f.close();
    }
    qDebug() << qmap;
}

WebDispatch::WebDispatch(QObject *parent) : QObject(parent),
    qnet( new QNetworkAccessManager( this ) )
{
    connections_fired = 0;
    connect( qnet, SIGNAL(finished(QNetworkReply*)), this, SLOT( onReplyFinished(QNetworkReply*)) );
}

void WebDispatch::init()
{
    QFile f( "sources.json" );

    if( ! f.exists() )
    {
        __process_websources();
        return;
    }

    QVariantMap qmap;

    if( ! Assist::Json::json_read( f, qmap ) )
    {
        __process_websources();
        return;
    }
    ELSE_DEBUG_P( "Sources is preconfigured." );

    // Конвертируем QVariantMap в QMap<QString, QStringList>
    QStringList keys = qmap.keys();
    foreach( QString key, keys )
    {
        this->qmap.insert( key, qmap.value( key ).toStringList() );
    }

    emit signal_AllSourcesHandled( this );
}

/**
 * @brief Получить валидную ссылку на сторонний ресурс.
 * @param key - ключ. Определяется из списка файлов в /web_path
 * @return Ссылку
 */
QUrl WebDispatch::getUrl(const QString &key)
{
    if( this->qmap.contains( key ) )
    {
        return this->qmap.value( key ).at(0);
    }

    return QUrl();
}

/**
 * @brief Получить пакет ссылок в виде QList< QUrl >
 * @param key - ключ идентификатор, см. описание getUrl
 * @return Пакет ссылок
 */
QList<QUrl> WebDispatch::getUrlPack(const QString &key)
{
    if( qmap.contains( key ) )
    {
        QList< QUrl > qul;

        foreach( QString str, qmap.value( key ) )
        {
            qul << QUrl( str );
        }

        return qul;
    }

    __debug_p( "Error: Not Contains" << key );

    return QList< QUrl >();
}

/**
 * @brief Получить пакет ссылок на источники версий.
 * @return Пакет источников versions.json
 */
QList<QUrl> WebDispatch::getVersionsPack()
{
    QList< QUrl > pack = getUrlPack( "sources" );

    return pack;
}

/**
 * @brief Получить ссылку на конфиг указанной версии.
 * @param version
 * @return Веб ссылка.
 */
QString WebDispatch::createVersionConfigLink( const QString &version )
{
    return QString( "%1versions/%2/%2.json" ).arg( getUrl( "sources" ).toString(), version );
}

void WebDispatch::onReplyFinished(QNetworkReply *reply)
{
    connections_fired--;
    QString qurl = reply->url().toString();

    if( qurl.isEmpty() )
    {
        __debug_p( "Error with reply finished. qurl is empty" );
        return;
    }

    if( reply->errorString().contains( "not found" ) )
    {
        __debug_p( qurl << " is unavailable" );
        QMap< QString, QStringList >::iterator it = this->qmap.begin();
        while( it != this->qmap.end() )
        {
            QStringList l = it.value();
            if( l.contains( qurl ) )
            {
                l.removeAll( qurl );
                this->qmap.insert( it.key(), l );
            }
            it++;
        }
    }
    ELSE_DEBUG_P( qurl << " OK." );

    if( connections_fired < 1 )
    {
        __debug_p( "All request handled" );

        QFile f( "sources.json" );
        QVariantMap qmap;
        QMap< QString, QStringList >::iterator it =this-> qmap.begin();

        while( it != this->qmap.end() )
        {
            qmap.insert( it.key(), it.value() );
            it++;
        }

        if( ! Assist::Json::json_write( &f, qmap ) )
        {
            __debug_p( "Could not write sources.json" );
        }

        emit signal_AllSourcesHandled( this );
    }
}

