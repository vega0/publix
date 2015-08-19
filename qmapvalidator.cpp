#include "qmapvalidator.h"
#include "assist.h"

#define __CLASS__ "QMapValidator"

QMapValidator::QMapValidator()
{
}

QMapValidator::QMapValidator(QStringList initial, QVariantMap *valider)
{
    params = initial;

    params.append("test123");

    this->valider = valider;

}

bool QMapValidator::isValid()
{
    __debug_p( params );

    if( params.isEmpty() )
    {
        __error_p( "List is empty." );
        return false;
    }

    foreach( QString param, params )
    {
        __debug_p( "Checking" << param );
        if( ! valider->contains( param ) )
            return false;
    }

    return true;
}

bool QMapValidator::addValid(const QString &param)
{
    if( ! params.contains( param ) )
    {
         __debug_p( param << "ADDED" )
        params.append( param );
        __debug_p( param << params );
        return true;
    }

    return false;
}
