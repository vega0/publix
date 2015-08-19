#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>
#include <QVariantMap>
#include <QVariant>

typedef QMap< int, QVariant > InsecurePairs;

namespace User{
class Config;
}

class Config : public QObject
{
    Q_OBJECT

    QVariantMap * qmap;
    InsecurePairs *qimap;

    static QMap< QString, Config* > *ConfigCache;

public:
    explicit Config(QObject *parent = 0, const QString &path = tr( ":/gear.json" ));

    QVariant GetValue( const QString &key );
    bool Contains( const QString &key );
    inline QString GetValueS( const QString &key )
    {
        return GetValue( key ).toString();
    }

    inline QVariantMap GetMap( const QString &key )
    {
        return GetValue( key ).toMap();
    }

    static Config * GetConfig( const QString &basename );

signals:
    void signal_GetHandler( const QString &key, const QVariant &value );

};

#endif // CONFIG_H
