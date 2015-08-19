#include "config.h"
#include "assist.h"

#define __CLASS__ "CoNfIG -"

QMap< QString, Config* > *Config::ConfigCache = new QMap< QString, Config* >;

Config::Config(QObject *parent, const QString &path) : QObject(parent)
{
    //RUN_ONCE( onc1, qmap = new QVariantMap(); Q_CHECK_PTR( qmap ) );

    qmap = new QVariantMap;

    Q_CHECK_PTR( qmap );

    if( !Assist::Json::Json_Read( path, *qmap ) )
    {
        __debug_p( "Config file"  << path <<  " is not loaded. " );

        //If some problems in code, must create track of this troubles for troubleshooting.
    }
    else
    {
        QString basename = QFileInfo( path ).baseName();
        if( ! ConfigCache->contains( basename ) )
        {
            ConfigCache->insert( basename, this );

            __debug_p( "CACHE : Adding config " << basename << " to cache." );
        }
    }
}

/**
 * @brief Получить QVarint из конфига по ключу.
 * @param key - строковый ключ
 * @return
 */
QVariant Config::GetValue(const QString &key)
{
    if( qmap->contains( key ) )
    {
        QVariant qvar = qmap->value( key );

        emit signal_GetHandler( key, qvar );

        return qvar;
    }

    __debug_p( "Key error '" << key << "'" );

    return QVariant();
}

bool Config::Contains(const QString &key)
{
    if( qmap->contains( key ) )
        return true;

    return false;
}

Config *Config::GetConfig(const QString &basename)
{
    if( ConfigCache->contains( basename ) )
    {
        return ConfigCache->value( basename );
    }

    return new Config( 0, QString( ":/%1.json" ).arg( basename ) );
}
