#include "jsonlibrary.h"
#include "assist.h"

JsonLibrary::JsonLibrary( QVariantMap lib )
{
    this->name = lib.value( "name" ).toString();

    if( lib.contains( "rules" ) )
    {
        this->rules = JsonRules( lib.value( "rules" ).toList() );
    }

    metalib = lib;
}

/**
 * @brief Получить универсальный путь.
 * @return универсальный путь.
 */
QString JsonLibrary::getNormalPath()
{
    if( ! normal_path.isEmpty() ) return normal_path;

    QStringList parts = this->name.split( ":" );

    QString st1part = parts.at(0);
    QString basic = QString( "%1%2%3%2%4%2" )
            .arg( st1part.replace( ".", QDir::separator() ), QDir::separator(), parts.at(1), parts.at(2) );
    basic.append( QString( "%1-%2" ).arg( parts.at(1), parts.at(2) ) );

    if( metalib.contains( "natives" ) )
    {
        QVariantMap natives = metalib.value( "natives" ).toMap();

        if( natives.contains( CURRENT_OS ) )
        {
            basic.append( QString( "-%1" ).arg( natives.value( CURRENT_OS ).toString() ) );
        }
    }

    basic.append( ".jar" );

    normal_path = basic;

    return basic;
}

bool JsonLibrary::isNotToExtract()
{
    if( metalib.contains( "extract" ) )
    {
        return false;
    }

    return true;
}

