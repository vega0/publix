#ifndef DIRDISPATCH_H
#define DIRDISPATCH_H

#include <QObject>

#include "config.h"

typedef QPair< const QString&, const QString& > ConstPair;
typedef QList< ConstPair > Replacement;

class DirDispatch : public QObject
{
    Q_OBJECT

    Config *fconf;
    Replacement *repl;

private:
    QString __preprocess( QString str );
    QString __concat( QString str1, QString str2 );

public:
    explicit DirDispatch(QObject *parent = 0);

    QString buildPath( const QString &section, const QString &append );
    void setReplaces( Replacement *repl );

signals:

public slots:
};

#endif // DIRDISPATCH_H
