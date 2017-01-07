#include "place.h"
#include "locationmanager.h"

Place::Place(QObject *parent) : QObject(parent) {
    id = LocationManager::autoLocation;
}

Place &Place::operator=(const Place &other) {
    id = other.id;
    name = other.name;
    country = other.country;
    coordinate = other.coordinate;
    return *this;
}
