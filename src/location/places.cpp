#include "places.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QTextStream>

// TODO: Лучше каждый раз вытягивать список городов заново, а не работать с локальным.

Places::Places(QObject *parent) : QObject(parent) {

}

bool Places::readLocalFile() {
    clear();
    QFile file("D:/Downloads/city.list.json/city.list.json"); // TODO: Положить файл рядом с приложением, имя файла и путь - в ini.
    if  (!file.open(QIODevice::ReadOnly)) {
        return false;
    }
    while (!file.atEnd()) { // TODO: Чтение файла вынести в отдельный поток.
        // TODO: Сделать проверки на существование всех элементов и атрибутов, на правильность структуры, на корректность значений; менять объект только в случае успеха.
        QJsonDocument jsonDocument = QJsonDocument::fromJson(file.readLine());
        QJsonObject jsonObjectMain = jsonDocument.object();
        int id = jsonObjectMain.value("_id").toInt();
        QString name = jsonObjectMain.value("name").toString();
        QString country = jsonObjectMain.value("country").toString();
        QJsonObject jsonObjectCoord = jsonObjectMain.value("coord").toObject();
        QGeoCoordinate location(jsonObjectCoord.value("lat").toDouble(), jsonObjectCoord.value("lon").toDouble());
        //        qDebug() << id << name << country << location.latitude() << location.longitude();
        ids.append(id);
        names.append(name);
        countries.append(country);
        locations.append(location);
    }
    file.close();
    return true;
}

void Places::clear() {
    ids.clear();
    names.clear();
    countries.clear();
    locations.clear();
}
