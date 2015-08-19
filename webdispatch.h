#ifndef WEBDISPATCH_H
#define WEBDISPATCH_H

#include <QObject>
#include <QVariantMap>
#include <QList>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#include "defines/entry.h"

class WebDispatch : public QObject
{
    Q_OBJECT

    QMap< QString, QStringList > qmap;
    QNetworkAccessManager *qnet;
    unsigned int connections_fired;

    void __process_websources();

public:
    explicit WebDispatch(QObject *parent = 0);

    void init();
    QUrl getUrl( const QString &key );
    QList< QUrl > getUrlPack( const QString &key );
    QList< QUrl > getVersionsPack();

    QString createVersionConfigLink( const QString &version );

signals:
    void signal_AllSourcesHandled( WebDispatch *webdispatch );
    void signal_SourceHandleStarted();

private slots:
    void onReplyFinished( QNetworkReply *reply );
};

#endif // WEBDISPATCH_H
