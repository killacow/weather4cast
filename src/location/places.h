#ifndef PLACES_H
#define PLACES_H

#include <QObject>
#include <QList>
#include <QGeoCoordinate>

class Places : public QObject
{
    Q_OBJECT
public:
    explicit Places(QObject *parent = 0);
    bool readLocalFile();
    void clear();

protected:
    QList<int> ids;
    QStringList names;
    QStringList countries;
    QList<QGeoCoordinate> locations;
};

#endif // PLACES_H
