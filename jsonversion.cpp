#include "jsonversion.h"
#include "assist.h"

#define __CLASS__ "]JsonVersion["

JsonVersion::JsonVersion( QVariantMap jsonMap ) :
    QMapValidator( QStringList( { "id", "libraries", "type", "minecraftArguments"} ), jsonMap )
{
    addValid( QObject::tr( "assets" ) );
    addValid( QObject::tr( "mainClass" ) );
    addValid( QObject::tr( "bullshit" ) );

    if( jsonMap.isEmpty() )
    {
        __debug_p( "Initial map is empty" );
        return;
    }

    version_id          = jsonMap.value( "id" ).toString();
    version_type        = jsonMap.value( "type" ).toString();
    minecraft_args      = jsonMap.value( "minecraftArguments" ).toString();
    minecraft_mainclass = jsonMap.value( "mainClass" ).toString();
    version_assets_id   = jsonMap.value( "assets" ).toString();

    QVariantList libs = jsonMap.value( "libraries" ).toList();
    foreach( QVariant lib, libs )
    {
        jlibs << JsonLibrary( lib.toMap() );
    }


#ifdef QT_DEBUG
    unsigned int c = 0;
    foreach( JsonLibrary lib, jlibs )
    {
        if( lib.rules.isAllowed() && lib.isNotToExtract() )
        {
            c++;
        }
    }

    __debug_p( "Allowed libs to this os is " << c );
#endif
}

QString JsonVersion::buildClassPath()
{
    return QString();
}

