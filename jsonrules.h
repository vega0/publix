#ifndef JSONRULES_H
#define JSONRULES_H

#include <QVariantList>

class JsonRules
{
private:
    QVariantList rules;

public:
    JsonRules();
    JsonRules( QVariantList rules );

    bool isAllowed();
};

#endif // JSONRULES_H
