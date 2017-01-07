#include "locationmanager.h"

// TODO: Во всех классах проверить удаляются ли контейнеры в деструкторах

#include "place.h"
#include "places.h"
#include "placesmodel.h"
#include "positioning.h"

LocationManager::LocationManager(QObject *parent) : QObject(parent) {
    connect(this, SIGNAL(currentPlaceUpdated(Place)), this, SLOT(onCurrentPlaceUpdated(Place)));
    currentPlace = new Place(this);
    places = new Places(this);
    placesModel = new PlacesModel(this, places, this);
    places->readLocalFile();
    positioning = new Positioning(this);
    connect(positioning, SIGNAL(responseRefreshLocation(bool,QGeoCoordinate)), this, SLOT(responseRefreshLocation(bool,QGeoCoordinate)));
}

void LocationManager::setCurrentPlace(int id) {
    if (id == autoLocation) {
        positioning->requestRefreshLocation();
    } else {
        QHash<int, Place *> places = this->places->getPlaces();
        if (places.contains(id)) {
            currentPlace = places.value(id);
            emit currentPlaceUpdated(*currentPlace);
        }
    }
}

PlacesModel *LocationManager::getPlacesModel() const {
    return placesModel;
}


void LocationManager::onCurrentPlaceUpdated(const Place &currentPlace) {
    // TODO: Не получилось выдернуть в QMLе координаты из параметров сигнала currentPlaceUpdated, поэтому сделал еще один сигнал.
    emit locationUpdated(currentPlace.coordinate);
}

void LocationManager::responseRefreshLocation(bool errorFlag, const QGeoCoordinate &location) {
    if (!errorFlag) {
        currentPlace->id = autoLocation;
        currentPlace->name.clear();
        currentPlace->country.clear();
        currentPlace->coordinate = location;
        emit currentPlaceUpdated(*currentPlace);
    }
}
