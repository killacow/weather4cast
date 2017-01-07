#include "placesmodel.h"
#include "place.h"
#include "places.h"
#include "locationmanager.h"

PlacesModel::PlacesModel(LocationManager *locationManager, Places *places, QObject *parent)
    : QAbstractListModel(parent)
    , locationManager(locationManager)
    , places(places){
    connect(places, SIGNAL(updated()), this, SLOT(updated()));
}

void PlacesModel::selectPlace(int index) {
    qDebug() << "place" << index;
    int id = LocationManager::autoLocation;
    if (index == 0) {

    } else {
        if (index < placeList.size()) {
            id = placeList.at(index)->id;
        }
    }
    locationManager->setCurrentPlace(id);
}

int PlacesModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()) {
        return 0;
    }

    return placeList.size();
}

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
}

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
