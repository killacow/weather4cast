#include "place.h"
#include "locationmanager.h"



/**
 * @brief Класс объектов-местоположений.
 * @param parent Предок согласно объектной иерархии Qt.
 */
Place::Place(QObject *parent) : QObject(parent) {
    id = LocationManager::autoLocation;
}



/**
 * @brief Оператор присваивания.
 */
Place &Place::operator=(const Place &other) {
    id = other.id;
    name = other.name;
    country = other.country;
    coordinate = other.coordinate;
    return *this;
}
