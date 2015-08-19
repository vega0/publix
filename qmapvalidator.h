#ifndef QMAPVALIDATOR_H
#define QMAPVALIDATOR_H

#include <QObject>
#include <QStringList>
#include <QVariantMap>

class QMapValidator
{
private:
    QStringList params;
    QVariantMap *valider;

public:
    QMapValidator();
    QMapValidator( QStringList initial, QVariantMap *valider );
    bool isValid();

protected:
    bool addValid( const QString &param );
};

#endif // QMAPVALIDATOR_H
