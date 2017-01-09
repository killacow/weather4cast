#include "positioning.h"



/**
 * @brief Класс, реализующий определение местоположения Пользователя по IP-адресу его компьютера.
 * @param parent Предок согласно объектной иерархии Qt.
 */
Positioning::Positioning(QObject *parent) : QObject(parent) {
    networkAccessManager = new QNetworkAccessManager(this);
    connect(networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
}



/**
 * @brief Возвращает последнее определенное местоположение.
 */
const QGeoCoordinate &Positioning::getLocation() const {
    return location;
}



/**
 * @brief Инициирует определение местоположения.
 * @return Успешно ли прошла инициализация.
 */
bool Positioning::requestRefreshLocation() {
    if (false) { // TODO: Проверить на слишком высокую частоту запросов
        return false;
    }
    networkAccessManager->get(QNetworkRequest(QUrl("http://ip-api.com/xml")));
    return true;
}



/**
 * @brief Разбирает XML, полученный от сервиса определения местоположения и заполняет координаты.
 * @param xmlData Данные XML.
 * @param[out] location Местоположение согласно XML.
 * @return Успех/неуспех.
 */
bool Positioning::parseLocationXML(const QByteArray &xmlData, QGeoCoordinate *location) {
    // TODO: Сделать проверки на существование всех элементов и атрибутов, на правильность структуры, на корректность значений; менять объект только в случае успеха.
    double latitude = qQNaN();
    double longitude = qQNaN();
    QXmlStreamReader xml(xmlData);
    while (!xml.atEnd()) {
        xml.readNext();
        if (xml.isStartElement()) {
            if (xml.name() == "lat") {
                bool ok = false;
                double tmp = xml.readElementText().toDouble(&ok);
                if (ok) {
                    latitude = tmp;
                }
            } else if (xml.name() == "lon") {
                bool ok = false;
                double tmp = xml.readElementText().toDouble(&ok);
                if (ok) {
                    longitude = tmp;
                }
            }
        }
    }
    if (!xml.hasError() && !qIsNaN(latitude) && !qIsNaN(longitude)) {
        location->setLatitude(latitude);
        location->setLongitude(longitude);
        return true;
    } else {
        return false;
    }
}



/**
 * @brief Делает последнее определенное местоположение !isValid.
 */
void Positioning::clearLocation() {
    location.setLatitude(qQNaN());
    location.setLongitude(qQNaN());
}



/**
 * @brief Слот-обработчик ответа от сервиса определения местоположения.
 * @param reply Ответ.
 */
void Positioning::replyFinished(QNetworkReply *reply) {
    if (!reply->error()) {
        if (parseLocationXML(reply->readAll(), &location)) {
            emit responseRefreshLocation(false, location);
        } else {
            emit responseRefreshLocation(true, location);
        }
    } else {
        emit responseRefreshLocation(true, location);
    }
    reply->deleteLater();
}
