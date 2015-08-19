#include "jsonrules.h"
#include "assist.h"

JsonRules::JsonRules()
{
}

JsonRules::JsonRules( QVariantList rules )
{
    JsonRules();

    this->rules = rules;
}

bool JsonRules::isAllowed()
{
    if( rules.isEmpty() ) return true;

    bool is_allowed = false;
    bool is_disallowed = false;

    foreach( QVariant metarule, rules )
    {
        QVariantMap rule = metarule.toMap();
        QString action = rule.value( "action" ).toString();
        QPair< QString, bool > pair;

        if( ! rule.contains( "os" ) )
        {
            pair.first = action;
            pair.second = true;
        }
        else
        {
            QString osname = rule.value( "os" ).toMap().value( "name" ).toString();

            if( osname == CURRENT_OS )
            {
                pair.first = action;
                pair.second = true;
            }
        }

        //Обрабатываем ключи.
        if( pair.first == "allow" )
            is_allowed = pair.second;
        else if( pair.first == "disallow" )
            is_disallowed = pair.second;
    }

    return is_allowed && ! is_disallowed;
}

