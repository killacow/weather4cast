#include "positioning.h"

Positioning::Positioning(QObject *parent) : QObject(parent) {
    networkAccessManager = new QNetworkAccessManager(this);
    connect(networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
}



const QGeoCoordinate &Positioning::getLocation() const {
    return location;
}



bool Positioning::requestRefreshLocation() {
    if (false) { // TODO: Проверить на слишком высокую частоту запросов
        return false;
    }
    networkAccessManager->get(QNetworkRequest(QUrl("http://ip-api.com/xml"))); // FIXME: to ini
    return true;
}


bool Positioning::parseLocationXML(const QByteArray &xmlData, QGeoCoordinate *location) {
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



void Positioning::clearLocation() {
    location.setLatitude(qQNaN());
    location.setLongitude(qQNaN());
}



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

    //qDebug() << "location done";
    //qDebug() << location.isValid() << location.latitude() << location.longitude();

    reply->deleteLater();
}
