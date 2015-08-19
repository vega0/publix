#ifndef JSONLIBRARY_H
#define JSONLIBRARY_H

#include <QVariantMap>
#include <QDir>

#include "jsonrules.h"

class JsonLibrary
{

private:
    QVariantMap metalib;
    QString normal_path;

public:
    QString name;
    JsonRules rules;

    JsonLibrary( QVariantMap lib );
    QString getNormalPath();
    bool isNotToExtract();
};

#endif // JSONLIBRARY_H
