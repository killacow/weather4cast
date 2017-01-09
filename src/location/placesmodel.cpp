#include "placesmodel.h"
#include "place.h"
#include "places.h"
#include "locationmanager.h"

// TODO: Нужно отладить механизм обновления позиции на карте при первом обновлении.



/**
 * @brief Класс-модель для списка мест (местоположений, городов).
 * @param locationManager Главный геолокационный объект.
 * @param places Менеджер списка мест.
 * @param parent Предок согласно объектной иерархии Qt.
 */
PlacesModel::PlacesModel(LocationManager *locationManager, Places *places, QObject *parent)
    : QAbstractListModel(parent)
    , locationManager(locationManager)
    , places(places){
    connect(places, SIGNAL(updated()), this, SLOT(updated()));
    placeList.append(NULL);
}



/**
 * @brief Метод вызывается при выборе Пользователем местоположения из списка и транслирует это местоположение LocationManager'у.
 * @param index Индекс выбранного Пользователем местоположения в списке (не имеет ничего общего с его id).
 */
void PlacesModel::selectPlace(int index) {
    int id = LocationManager::autoLocation;
    if (index == 0) {

    } else {
        if (index < placeList.size()) {
            id = placeList.at(index)->id;
        }
    }
    locationManager->setCurrentPlace(id);
}



/**
 * @brief Возвращает количество строк в списке мест.
 * @see QAbstractListModel
 */
int PlacesModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()) {
        return 0;
    }
    return placeList.size();
}



/**
 * @brief Возвращает текст, отображаемый в каждом элементе списка мест.
 * @see QAbstractListModel
 */
QVariant PlacesModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }
    switch (role) {
    case Qt::DisplayRole: {
        int row = index.row();
        if (row == 0) {
            return "AUTO";
        } else {
            if (row < placeList.size()) {
                Place *p = placeList.at(row);
                return QString("%1, %2").arg(p->name).arg(p->country);
            }
        }
    }
    default:
        return QVariant();
    }
    return QVariant();
}



/**
 * @brief Позволяет по началу названия места узнать его индекс в списке.
 * @param text Начало названия места.
 * @return Индекс в списке. Если не найден - 0.
 */
int PlacesModel::getIndexByText(QString text) {
    if (text.isEmpty()) {
        return 0;
    }
    for (int i = 0; i < placeList.size(); ++i) {
        if (placeList.at(i)) {
            if (placeList.at(i)->name.startsWith(text, Qt::CaseInsensitive)) {
                return i;
            }
        }
    }
    return 0;
}



/**
 * @brief Слот-обработчик сигнала о том что список мест был обновлен.
 */
void PlacesModel::updated() {
    emit layoutAboutToBeChanged();
    placeList.clear();
    placeList.append(NULL);

    // http://doc.qt.io/qt-5/qstringlist.html#sort
    // If you want to sort your strings in an arbitrary order, consider using the QMap class. For example, you could use a QMap<QString, QString> to create a case-insensitive ordering (e.g. with the keys being lower-case versions of the strings, and the values being the strings), or a QMap<int, QString> to sort the strings by some integer index.
    QMap<QString, Place *> map;
    foreach (Place *p, places->getPlaces()) {
        map.insert(p->name, p);
    }

    placeList.append(map.values());
    emit layoutChanged();
}
