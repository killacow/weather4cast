#ifndef LOCATIONMANAGER_H
#define LOCATIONMANAGER_H

#include <QObject>
#include <QGeoCoordinate>

class Place;
class Places;
class PlacesModel;
class Positioning;

class LocationManager : public QObject
{
    Q_OBJECT
public:
    enum { autoLocation = -1 };
    explicit LocationManager(QObject *parent = 0);

    void setCurrentPlace(int id);

    PlacesModel *getPlacesModel() const;

signals:
    void currentPlaceUpdated(const Place &currentPlace);
    void locationUpdated(const QGeoCoordinate &location);

public slots:

protected:
    Place *currentPlace;
    Places *places;
    PlacesModel *placesModel;
    Positioning *positioning;

protected slots:
    void onCurrentPlaceUpdated(const Place &currentPlace);
    void responseRefreshLocation(bool errorFlag, const QGeoCoordinate &location);
};

#endif // LOCATIONMANAGER_H
