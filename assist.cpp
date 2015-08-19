#include "assist.h"

#define __CLASS__ "*`ASSISTANT`*"



#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
/**
 * @brief Метод чтения Json файлов.
 * @param file
 * @param vmap
 * @return
 */
bool Assist::Json::json_read(QFile & file, QVariantMap & vmap)
{
    if(file.open(QFile::ReadOnly))
    {
        QJsonParseError jerror;
        QJsonDocument jdoc = QJsonDocument::fromJson(file.readAll(), &jerror);
        file.close();
        if(jerror.error != QJsonParseError::NoError)
        {
#ifdef QT_DEBUG
            qCritical() << Q_FUNC_INFO << "Can't parse '" << file.fileName() << "'!" << endl;
#endif
            return false;
        }

        vmap = jdoc.object().toVariantMap();
        return true;
    }
    return false;
}

bool Assist::Json::Json_Read(const QString &path, QVariantMap &vmap)
{
    QFile jfile(path);

    if(!jfile.open(QIODevice::ReadOnly))
    {
        __debug_p("Error due opening" << path << jfile.errorString());
        return false;
    }

    QJsonParseError jerror;
    QJsonDocument jdoc = QJsonDocument::fromJson(jfile.readAll(), &jerror);
    jfile.close();
    if(jerror.error != QJsonParseError::NoError)
    {
        __debug_p( "Json read parser error, " << jerror.errorString() << " in path " << path )
        return false;
    }

    vmap = jdoc.object().toVariantMap();

#ifdef QT_DEBUG
    if(vmap.isEmpty())
    {
        qDebug() << "Json file" << path << "is empty";
    }
#endif

    return true;
}

#include <QDateTime>
#include <QCryptographicHash>
#include <QTime>
/**
 * Реализация метода получения единичного хэша, зависящего от времени.
 * @brief Assist::Time::Time_HashDump
 * @return
 */
QString Assist::Time::Time_HashDump()
{
    return QString(QCryptographicHash::hash(QVariant(QTime::currentTime().toString()).toByteArray(), QCryptographicHash::Md5).toHex()).toLower();
}


#include <QRegExp>
/**
 * Функция парсинга названия файла.
 * @brief Assist::Network::Reply_ParseFilename
 * @param reply
 * @return
 */
QString Assist::Network::Reply_ParseFilename(const QNetworkReply *reply)
{
    QRegExp rg("filename=\"([^\"]+)\"");
    rg.indexIn(reply->rawHeader("Content-Disposition"));
    Q_ASSERT(!rg.capturedTexts().at(1).isEmpty());
    return rg.capturedTexts().at(1);
}

/**
 * Дамп Json конфига в фаил.
 * @brief Assist::Json::json_write
 * @param file
 * @param data
 * @return
 */
bool Assist::Json::json_write(QFile *file, const QVariantMap &data)
{
    if(data.isEmpty())
        return false;

    if(file->exists())
        file->remove();

    if(!file->open(QIODevice::WriteOnly))
            return false;

    file->write(QJsonDocument(QJsonObject::fromVariantMap(data)).toJson());
    file->close();
    return true;
}

/**
 * Реализация вспомогательной функции слияния двух хешей по определенному алгоритму.
 * @brief Assist::Hash::Hash_Generate
 * @param f1
 * @param f2
 * @param alg
 * @return
 */
QByteArray Assist::Hash::Hash_Generate(QByteArray f1, QByteArray f2, QCryptographicHash::Algorithm alg)
{
    QCryptographicHash c(alg);
    c.addData(f1); c.addData(f2);
    return c.result();
}

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
/**
 * Реализация метода загрузки файла из интернета.
 * @brief Assist::Network::Network_DownloadFile
 * @param url - интернет адресс
 * @param path - путь сохранения.
 * @return
 */
bool Assist::Network::Network_DownloadFile(const QString &url, const QString &path)
{
    QNetworkAccessManager n_manager;
    QNetworkReply *reply = n_manager.get(QNetworkRequest(url));
    QEventLoop loop;
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    QUrl u_url(url);
    QFileInfo info(u_url.path());
#ifdef QT_DEBUG
    qDebug() << __CLASS__ << "Downloading" << url << "to" << path << "/" << info.fileName();
#endif
    loop.exec();

    if(!QFileInfo(path).exists())
        QDir().mkpath(path);

    QFile file(path + QDir::separator() + info.fileName());
    if(!file.open(QIODevice::WriteOnly))
    {
#ifdef QT_DEBUG
        qDebug() << __CLASS__ << path + QDir::separator() + info.fileName() << "Can't create file" << file.errorString();
#endif
        return false;
    }
    file.write(reply->readAll());
    file.close();
    delete reply;

#ifdef QT_DEBUG
    qDebug() << __CLASS__ << path + QDir::separator() + info.fileName() << "downloaded successful";
#endif
    return true;
}

/**
 * Имлементация метода считывания json файла по интернет адресу.
 * @brief Assist::Network::Network_JFromUrl
 * @param url
 * @return
 */
QVariantMap Assist::Network::Network_JFromUrl(const QString &url)
{
    QNetworkAccessManager m;
    QNetworkReply *reply = m.get(QNetworkRequest(url));
    QEventLoop loop;
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    if(reply->error())
    {
#ifdef QT_DEBUG
        qDebug() << __CLASS__ << "Reply error" << reply->errorString();
#endif
        delete reply;
        return QVariantMap();
    }

    QJsonParseError jerror;
    QJsonDocument jdoc = QJsonDocument::fromJson(reply->readAll(), &jerror);

    delete reply;

    if(jerror.error != QJsonParseError::NoError)
    {
#ifdef QT_DEBUG
        qDebug() << __CLASS__ << "Can't read json from" << url
                 << "Errstr:" << jerror.errorString();
#endif
        return QVariantMap();
    }

    return jdoc.object().toVariantMap();
}

QString Assist::Network::Network_GetRequest(const QString &url)
{
    QNetworkAccessManager m;
    QNetworkReply *reply = m.get(QNetworkRequest(url));
    QEventLoop loop;
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    QString text = reply->readAll();

    __DEBUG_P("Request from" << url << "answer is" << text);

    if(text.isEmpty())
    {
        __DEBUG_P(reply->errorString());
    }

    return text;
}
