#include "dirdispatch.h"
#include "assist.h"

#define __CLASS__ "DirDispatch^"


QString DirDispatch::__preprocess( QString str )
{
    if( str.contains( "{d}" ) )
    {
        str = str.replace( "{d}", QDir::separator() );
    }

    if( repl )
    {
        foreach( ConstPair pair, *repl )
        {
            str = str.replace( QString( "{%1}" ).arg( pair.first ), pair.second );
        }
    }

#ifdef QT_DEBUG
    if( str.contains( "{" ) && str.contains( "}" ) )
        __debug_p( str << "Almost edited" );
#endif

    return str;
}

QString DirDispatch::__concat(QString str1, QString str2)
{
    return QString( "%1%2%3" ).arg( str1, QDir::separator(), str2 );
}

DirDispatch::DirDispatch(QObject *parent) : QObject(parent)
{
    fconf = Config::GetConfig( tr( "dirs" ) );

    Q_CHECK_PTR( fconf );
}

/**
 * @brief Процессинг локальных путей, выдает абсолютный путь до назначения.
 * @param section - строковый параметр в конфиге
 * @param append - добавочный путь
 * @return абсолютный путь
 */
QString DirDispatch::buildPath( const QString &section, const QString &append )
{
    if( ! fconf->Contains( section ) )
    {
        __debug_p( "Can't build path." << section << "not exists." );
        return QString( "no-path" );
    }

    QVariantMap conf = fconf->GetMap( section );

    QString initial_dir = __preprocess( conf.value( "initial" ).toString() );

    if( ! QDir( initial_dir ).exists() )
    {
        QDir().mkpath( initial_dir );
    }
    QString structure = __preprocess( conf.value( "structure" ).toString() );
    QString fullpath = QDir( __concat(__concat( initial_dir, structure ), __preprocess(append)) ).absolutePath();


    __debug_p( "Builded path is" << fullpath );


    return fullpath;
}

void DirDispatch::setReplaces(Replacement *repl)
{
    this->repl = repl;

    Q_CHECK_PTR( this->repl );
}

