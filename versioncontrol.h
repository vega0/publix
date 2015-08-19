#ifndef VERSIONCONTROL_H
#define VERSIONCONTROL_H

#include <QObject>

#include "webdispatch.h"
#include "jsonversion.h"
#include "dirdispatch.h"

class VersionControl : public QObject
{
    Q_OBJECT

    WebDispatch *webdispatch;
    DirDispatch *dirdispatch;

    QList< QVariantMap > jversions;

    QString filter;

public:
    explicit VersionControl(QObject *parent = 0);

    void setWebDispatcher( WebDispatch *webdispatch );
    void setDirDispatcher( DirDispatch *dirdispatch );

    bool initial();
    void setFilter( const QString &str );
    QStringList getVersions();

    bool versionExists( const QString &version );
    bool selectVersion( const QString &version );

signals:
    void signal_VersionsSet( QStringList slist );
public slots:
};

#endif // VERSIONCONTROL_H
