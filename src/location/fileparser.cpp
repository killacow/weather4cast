#include "fileparser.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "place.h"
#include <QTextStream>



/**
 * @brief Класс разбирает файл с JSON-объектами городов.
 * Вынесен в отдельный поток, потому что файл большой и его разбор занимает много времени.
 * @param parent Предок согласно объектной иерархии Qt.
 */
FileParser::FileParser(QObject *parent) : QThread(parent) {

}



/**
 * @brief Инициирует разбор файла.
 * @param fileName Имя файла.
 */
void FileParser::parseFile(const QString &fileName) {
    this->fileName = fileName;
    this->start();
}



/**
 * @brief Статический метод, разбирающий JSON-объект одного города.
 * @param jsonData Массив данных JSON-объекта одного города.
 * @param[out] place Объект-место (объект-город), который будет проинициализирован в соответствии с полями JSON-объекта. Не NULL!
 * @return Успех/неуспех.
 */
bool FileParser::parseJson(const QByteArray &jsonData, Place *place) {
    // TODO: Сделать проверки на существование всех элементов и атрибутов, на правильность структуры, на корректность значений; менять объект только в случае успеха.
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonData);
    QJsonObject jsonObjectMain = jsonDocument.object();
    place->id = jsonObjectMain.value("_id").toInt();
    place->name = jsonObjectMain.value("name").toString();
    place->country = jsonObjectMain.value("country").toString();
    QJsonObject jsonObjectCoord = jsonObjectMain.value("coord").toObject();
    place->coordinate.setLatitude(jsonObjectCoord.value("lat").toDouble());
    place->coordinate.setLongitude(jsonObjectCoord.value("lon").toDouble());
    return true;
}



/**
 * @brief Метод, выполняемый в другом потоке.
 * @see http://doc.qt.io/qt-5/qthread.html
 */
void FileParser::run() {
    places.clear();
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        while(!file.atEnd()) {
            Place *place = new Place(); // no memory leak
            if (parseJson(file.readLine(), place)) {
                places.insert(place->id, place);
            }
        }
        file.close();
        emit done(false, &places);
    } else {
        emit done(true, &places);
    }
}
