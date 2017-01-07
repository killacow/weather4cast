#ifndef PLACES_H
#define PLACES_H

#include <QObject>
#include <QHash>
#include <QGeoCoordinate>

class Place;

class Places : public QObject
{
    Q_OBJECT
public:
    explicit Places(QObject *parent = 0);

    bool readLocalFile();
    void clear();

    QHash<int, Place *> getPlaces() const;

signals:
    void updated();

protected:
    QHash<int, Place *> places;
};

#endif // PLACES_H
