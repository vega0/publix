#ifndef ASSIST_H
#define ASSIST_H

#include "defines/entry.h"

#include <QVariantMap>
#include <QMap>
#include <QList>
#include <QVariant>
#include <QFile>
#include <QDir>
#include <QtDebug>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QUrl>

namespace Assist
{
    namespace Json
    {
        /**
         * @brief Функция чтения Json конфигов.
         * @param &file - файл для чтения
         * @param &map - карта, в которую будет сконвертирован Json конфиг
         * @return bool - статус чтения, false если где-то ошибка.
         */
        bool json_read(QFile &file, QVariantMap &map);
        bool json_write(QFile *dst, const QVariantMap &jobj);

        bool Json_Read(const QString &path, QVariantMap &vmap);
    }

    namespace Time
    {
        QString Time_HashDump();
    }

    namespace Network
    {
        QString Reply_ParseFilename(const QNetworkReply *reply);
        bool Network_DownloadFile(const QString &url, const QString &path);
        QString Network_GetRequest(const QString &url);
        /*
         * Функция считывания json из интернет адреса.
         */
        QVariantMap Network_JFromUrl(const QString &url);
    }

    namespace Hash
    {
        QByteArray Hash_Generate(QByteArray f1, QByteArray f2, QCryptographicHash::Algorithm alg);
    }

    //Пространство имен вспомогательных функций, для работы с контейнерами данных.
    namespace Data
    {
        //Шаблон функции хеширования ключей карты.
        //Реализация в хедере в связи с ограничениями компилятора языка Си++
        template<class T1, class T2> QByteArray Map_GetHashOfValues(const QMap<T1, T2> *map)
        {
            QList<T2> lst;
            for(typename QMap<T1, T2>::const_iterator it = map->begin(); it != map->end(); ++it)
                lst.append(it.value());
            Q_ASSERT(!lst.isEmpty());
            QCryptographicHash crypt(QCryptographicHash::Md5);
            foreach(T2 item, lst)
                crypt.addData(QVariant(item).toByteArray());
            return crypt.result();
        }

        //Конвертирование Любой типовой карты в карту с плавающим типом.
        template<class T1, class T2> QVariantMap Map_ConvertToVariantMap(const QMap<T1, T2> *map)
        {
            QVariantMap vmap;
            for(typename QMap<T1, T2>::const_iterator it = map->begin(); it != map->end(); ++it)
                vmap.insert(it.key(), it.value());
            Q_ASSERT(!vmap.isEmpty());
            return vmap;
        }

#ifdef QT_DEBUG
        //Вывести карту на экран.
        template<class T1, class T2> void Map_PrintToConsole(const QMap<T1, T2> *map)
        {
            for(typename QMap<T1, T2>::const_iterator it = map->begin(); it != map->end(); ++it)
            {
                qDebug() << it.key() << "/" << it.value();
            }
        }
#endif
    }
}

#endif // ASSIST_H
