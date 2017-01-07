#include "fileparser.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "place.h"

FileParser::FileParser(QObject *parent) : QThread(parent) {

}

void FileParser::parseFile(const QString &fileName) {
    this->fileName = fileName;
    this->start();
}

void FileParser::run() {
    places.clear();
    // Открываем файл
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        while (!file.atEnd()) { // FIXME: Чтение файла вынести в отдельный поток.
            // TODO: Сделать проверки на существование всех элементов и атрибутов, на правильность структуры, на корректность значений; менять объект только в случае успеха.
            QJsonDocument jsonDocument = QJsonDocument::fromJson(file.readLine());
            QJsonObject jsonObjectMain = jsonDocument.object();
            Place *place = new Place();
            place->id = jsonObjectMain.value("_id").toInt();
            place->name = jsonObjectMain.value("name").toString();
            place->country = jsonObjectMain.value("country").toString();
            QJsonObject jsonObjectCoord = jsonObjectMain.value("coord").toObject();
            place->coordinate.setLatitude(jsonObjectCoord.value("lat").toDouble());
            place->coordinate.setLongitude(jsonObjectCoord.value("lon").toDouble());
            places.insert(place->id, place);
        }
        file.close();
        emit done(false, &places);
    } else {
        emit done(true, &places);
    }
}
