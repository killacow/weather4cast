#include "places.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QTextStream>

#include "place.h"

// FIXME: Написать пространный комментарий о том что лучше каждый раз вытягивать список городов заново, а не работать с локальным.

Places::Places(QObject *parent) : QObject(parent) {

}

bool Places::readLocalFile() {
    clear();
    QFile file("D:/Downloads/city.list.json/city.list.json"); // TODO: Положить файл рядом с приложением, имя файла и путь - в ini.
    if  (!file.open(QIODevice::ReadOnly)) {
        return false;
    }
    while (!file.atEnd()) { // FIXME: Чтение файла вынести в отдельный поток.
        // TODO: Сделать проверки на существование всех элементов и атрибутов, на правильность структуры, на корректность значений; менять объект только в случае успеха.
        QJsonDocument jsonDocument = QJsonDocument::fromJson(file.readLine());
        QJsonObject jsonObjectMain = jsonDocument.object();
        Place *place = new Place(this);
        place->id = jsonObjectMain.value("_id").toInt();
        place->name = jsonObjectMain.value("name").toString();
        place->country = jsonObjectMain.value("country").toString();
        QJsonObject jsonObjectCoord = jsonObjectMain.value("coord").toObject();
        place->coordinate.setLatitude(jsonObjectCoord.value("lat").toDouble());
        place->coordinate.setLongitude(jsonObjectCoord.value("lon").toDouble());
        //        qDebug() << id << name << country << location.latitude() << location.longitude();
        places.insert(place->id, place);
    }
    file.close();
    emit updated();
    qDebug() << "places read";
    return true;
}

void Places::clear() {
    qDeleteAll(places);
    places.clear();
}

QHash<int, Place *> Places::getPlaces() const
{
    return places;
}


