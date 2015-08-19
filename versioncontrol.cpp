#include "versioncontrol.h"
#include "assist.h"

#define __CLASS__ "+Version$+"

VersionControl::VersionControl(QObject *parent) : QObject(parent)
{
}

void VersionControl::setWebDispatcher( WebDispatch *webdispatch )
{
    this->webdispatch = webdispatch;
    __debug_p( this->webdispatch->getUrl( "sources" ) );
    Q_CHECK_PTR( this->webdispatch );
}

void VersionControl::setDirDispatcher(DirDispatch *dirdispatch)
{
    this->dirdispatch = dirdispatch;
    Q_CHECK_PTR( this->dirdispatch );
}

bool VersionControl::initial()
{
    //Testing JsonVersion
    __mark( testcase1, "Harvest versions" );

    QStringList qlist;
    QList< QUrl > pack = webdispatch->getUrlPack( "sources" );

    foreach( QUrl qurl, pack )
    {
        qlist << (qurl.toString() + QString( "versions/versions.json" ) );
    }

    while( ! qlist.isEmpty() )
    {
        jversions << Assist::Network::Network_JFromUrl( qlist.takeFirst() );
    }

    __elapsed( testcase1, "Versions harvested in" );
    return true;
}

void VersionControl::setFilter(const QString &str)
{
    filter = str;
}

QStringList VersionControl::getVersions()
{
    QStringList total;

    foreach( QVariantMap jver, jversions )
    {
        QVariantList vers = jver.value( "versions" ).toList();

        foreach( QVariant qvar, vers )
        {
            QVariantMap ver = qvar.toMap();
            QString type = ver.value( "type" ).toString();
            if( type == this->filter )
            {
                total << ver.value( "id" ).toString();
            }
        }
    }

    emit signal_VersionsSet( total );

    return total;
}

bool VersionControl::versionExists(const QString &version)
{
    return false;
}

/**
 * @brief Выбор версии.
 * @param version - строковое название версии
 * @return true в случае успеха.
 */
bool VersionControl::selectVersion(const QString &version)
{
    return false;
}

