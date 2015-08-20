#ifndef JSONVERSION_H
#define JSONVERSION_H

#include <QVariantMap>
#include <QList>

#include "qmapvalidator.h"
#include "jsonlibrary.h"

class JsonVersion : public QMapValidator
{
public:
    QString version_id;
    QString version_type;
    QString minecraft_args;
    QString minecraft_mainclass;
    QString version_assets_id;

    QList< JsonLibrary > jlibs;

    JsonVersion( QVariantMap jsonMap );

    QString buildClassPath();
};

#endif // JSONVERSION_H
