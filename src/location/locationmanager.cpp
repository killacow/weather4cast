#include "locationmanager.h"
#include "place.h"
#include "places.h"
#include "placesmodel.h"
#include "positioning.h"



/**
 * @brief Класс, отвечающий за работу со всем что связано с географическим положением.
 * @param parent Предок согласно объектной иерархии Qt.
 */
LocationManager::LocationManager(QObject *parent) : QObject(parent) {
    connect(this, SIGNAL(currentPlaceUpdated(Place)), this, SLOT(onCurrentPlaceUpdated(Place)));
    currentPlace = new Place(this);
    places = new Places(this);
    placesModel = new PlacesModel(this, places, this);
    places->readLocalFile();
    positioning = new Positioning(this);
    connect(positioning, SIGNAL(responseRefreshLocation(bool,QGeoCoordinate)), this, SLOT(responseRefreshLocation(bool,QGeoCoordinate)));
}



/**
 * @brief Метод, устанавливающий текущее местоположение.
 * Под текущим местоположением здесь и далее понимается местоположение,
 * для которого должен быть определен прогноз погоды и которое должно быть отображено на карте.
 * @param id Код местоположения (поле _id из JSON-объекта). -1 означает "автоматически определенное местоположение" (по IP-адресу).
 */
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



/**
 * @return Модель представления списка мест.
 */
PlacesModel *LocationManager::getPlacesModel() const {
    return placesModel;
}



/**
 * @brief Слот для дублирования сигнала.
 * TODO: Не получилось выдернуть в QMLе координаты из параметров сигнала currentPlaceUpdated, поэтому сделал еще один сигнал.
 * @param currentPlace Текущее местоположение.
 */
void LocationManager::onCurrentPlaceUpdated(const Place &currentPlace) {
    emit locationUpdated(currentPlace.coordinate);
}



/**
 * @brief Слот-обработчик завершения определения местоположения по IP.
 * @param errorFlag Индикатор ошибки.
 * @param location Координаты, определенные по IP-адресу.
 */
void LocationManager::responseRefreshLocation(bool errorFlag, const QGeoCoordinate &location) {
    if (!errorFlag) {
        currentPlace->id = autoLocation;
        currentPlace->name.clear();
        currentPlace->country.clear();
        currentPlace->coordinate = location;
        emit currentPlaceUpdated(*currentPlace);
    }
}
