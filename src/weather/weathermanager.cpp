#include "weathermanager.h"
#include "weather.h"
#include "currentweather.h"
#include "forecast.h"
#include "forecastmodel.h"
#include "utils.h"
#include "location/place.h"
#include "location/locationmanager.h"

// http://api.openweathermap.org/data/2.5/forecast?q=London,us&units=metric&mode=xml&appid=ccc14cee93ba94cebca502708f6fca03

// TODO: Таймер на обновление погоды

WeatherManager::WeatherManager(QObject *parent) : QObject(parent) {
    networkAccessManager = new QNetworkAccessManager(this);
//    connect(networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

    currentWeather = new CurrentWeather(this);
    forecast = new Forecast(this);
    forecastModel = new ForecastModel(forecast, this);

    // TODO: Таймер на обновление погоды лучше заводить каждый раз после обновления.
    startTimer(10 * 60 * 1000);   // обновление // TODO: to ini

}

//QGeoCoordinate WeatherManager::getLocation() const {
//    return location;
//}

//void WeatherManager::setLocation(const QGeoCoordinate &value) {
//    location = value;
//}

CurrentWeather *WeatherManager::getCurrentWeather() const {
    return currentWeather;
}

//bool WeatherManager::requestRefresh() {
//    if (false) { // TODO: Проверить на слишком высокую частоту запросов, проверить на корректность местоположения.
//        return false;
//    }

//    QUrl address = QString("http://api.openweathermap.org/data/2.5/weather?lat=%1&lon=%2&units=metric&mode=xml&appid=ccc14cee93ba94cebca502708f6fca03")
//            .arg(QString::number(location.latitude(), 'f'))
//            .arg(QString::number(location.longitude(), 'f'));


//    networkAccessManager->get(QNetworkRequest(QUrl(address))); // TODO: to ini

//    return true;
//}

void WeatherManager::currentPlaceUpdated(const Place &currentPlace) {
    this->currentPlace = currentPlace;
    if (currentPlace.id == LocationManager::autoLocation) {
        requestCurrenWeather(currentPlace.coordinate);
        requestForecast(currentPlace.coordinate);
    } else {
        requestCurrenWeather(currentPlace.id);
        requestForecast(currentPlace.id);
    }
    qDebug() << "update req";

}

void WeatherManager::timerEvent(QTimerEvent *event) {
    Q_UNUSED(event);
    currentPlaceUpdated(currentPlace);
}

bool WeatherManager::requestCurrenWeather(int cityId) {
    if (false) { // TODO: Проверить на слишком высокую частоту запросов, проверить на корректность местоположения.
        return false;
    }
    QUrl address = QString("http://api.openweathermap.org/data/2.5/weather?id=%1&units=metric&mode=xml&appid=ccc14cee93ba94cebca502708f6fca03")
            .arg(QString::number(cityId));
    QNetworkReply *reply = networkAccessManager->get(QNetworkRequest(QUrl(address))); // TODO: to ini
    connect(reply, SIGNAL(finished()), this, SLOT(replyCurrentWeather()));
    return true;
}

bool WeatherManager::requestCurrenWeather(const QGeoCoordinate &location) {
    if (false) { // TODO: Проверить на слишком высокую частоту запросов, проверить на корректность местоположения.
        return false;
    }
    QUrl address = QString("http://api.openweathermap.org/data/2.5/weather?lat=%1&lon=%2&units=metric&mode=xml&appid=ccc14cee93ba94cebca502708f6fca03")
            .arg(QString::number(location.latitude(), 'f'))
            .arg(QString::number(location.longitude(), 'f'));
    QNetworkReply *reply = networkAccessManager->get(QNetworkRequest(QUrl(address))); // TODO: to ini
    connect(reply, SIGNAL(finished()), this, SLOT(replyCurrentWeather()));
    return true;
}

bool WeatherManager::requestForecast(int cityId) {
    if (false) { // TODO: Проверить на слишком высокую частоту запросов, проверить на корректность местоположения.
        return false;
    }
    QUrl address = QString("http://api.openweathermap.org/data/2.5/forecast?id=%1&units=metric&mode=xml&appid=ccc14cee93ba94cebca502708f6fca03")
            .arg(QString::number(cityId));
    QNetworkReply *reply = networkAccessManager->get(QNetworkRequest(QUrl(address))); // TODO: to ini
    connect(reply, SIGNAL(finished()), this, SLOT(replyForecast()));
    return true;
}

bool WeatherManager::requestForecast(const QGeoCoordinate &location) {
    if (false) { // TODO: Проверить на слишком высокую частоту запросов, проверить на корректность местоположения.
        return false;
    }
    QUrl address = QString("http://api.openweathermap.org/data/2.5/forecast?lat=%1&lon=%2&units=metric&mode=xml&appid=ccc14cee93ba94cebca502708f6fca03")
            .arg(QString::number(location.latitude(), 'f'))
            .arg(QString::number(location.longitude(), 'f'));
    QNetworkReply *reply = networkAccessManager->get(QNetworkRequest(QUrl(address))); // TODO: to ini
    connect(reply, SIGNAL(finished()), this, SLOT(replyForecast()));
    return true;
}

bool WeatherManager::parseCurrentWeatherXml(const QByteArray &xmlData, CurrentWeather *currentWeather) {
    // TODO: Сделать проверки на существование всех элементов и атрибутов, на правильность структуры, на корректность значений; менять объект только в случае успеха.
    QXmlStreamReader xml(xmlData);
    bool ok = true;
    while (!xml.atEnd()) {
        xml.readNext();
        if (xml.isStartElement()) {
            if (xml.name() == "city") {
                currentWeather->cityId = xml.attributes().value("id").toInt(&ok);
                currentWeather->cityName = xml.attributes().value("name").toString();
//                qDebug() << currentWeather->cityName;
            } else if (xml.name() == "coord") {
                currentWeather->cityCoord.setLongitude(xml.attributes().value("lon").toDouble(&ok));
                currentWeather->cityCoord.setLatitude(xml.attributes().value("lat").toDouble(&ok));
            } else if (xml.name() == "country") {
                currentWeather->cityCountry = xml.readElementText();
            } else if (xml.name() == "sun") {
                QDateTime dt = QDateTime::fromString(xml.attributes().value("rise").toString(), "yyyy-MM-ddTHH:mm:ss");
                dt.setTimeSpec(Qt::UTC);
                currentWeather->citySunRise = dt.toLocalTime();
                dt = QDateTime::fromString(xml.attributes().value("set").toString(), "yyyy-MM-ddTHH:mm:ss");
                dt.setTimeSpec(Qt::UTC);
                currentWeather->citySunSet = dt.toLocalTime();
            } else if (xml.name() == "temperature") {
                currentWeather->temperatureValue = xml.attributes().value("value").toDouble(&ok);
                currentWeather->temperatureMin = xml.attributes().value("min").toDouble(&ok);
                currentWeather->temperatureMax = xml.attributes().value("max").toDouble(&ok);
                currentWeather->temperatureUnit = xml.attributes().value("unit").toString();
            } else if (xml.name() == "humidity") {
                currentWeather->humidityValue = xml.attributes().value("value").toDouble(&ok);
                currentWeather->humidityUnit = xml.attributes().value("unit").toString();
            } else if (xml.name() == "pressure") {
                currentWeather->pressureValue = xml.attributes().value("value").toDouble(&ok);
                currentWeather->pressureUnit = xml.attributes().value("unit").toString();
            } else if (xml.name() == "speed") {
                currentWeather->windSpeedValue = xml.attributes().value("value").toDouble(&ok);
                currentWeather->windSpeedName = xml.attributes().value("name").toString();
            } else if (xml.name() == "direction") {
                currentWeather->windDirectionValue = xml.attributes().value("value").toDouble(&ok);
                currentWeather->windDirectionCode = xml.attributes().value("code").toString();
                currentWeather->windDirectionName = xml.attributes().value("name").toString();
            } else if (xml.name() == "clouds") {
                currentWeather->cloudsValue = xml.attributes().value("value").toDouble(&ok);
                currentWeather->cloudsName = xml.attributes().value("name").toString();
            } else if (xml.name() == "visibility") {
                currentWeather->visibilityValue = xml.attributes().value("value").toDouble(&ok);
            } else if (xml.name() == "precipitation") {
                currentWeather->precipitationMode = xml.attributes().value("mode").toString();
            } else if (xml.name() == "weather") {
                currentWeather->weatherNumber = xml.attributes().value("number").toInt(&ok);
                currentWeather->weatherValue = xml.attributes().value("value").toString();
                currentWeather->weatherIcon = xml.attributes().value("icon").toString();
            } else if (xml.name() == "lastupdate") {
                QDateTime dt = QDateTime::fromString(xml.attributes().value("value").toString(), "yyyy-MM-ddTHH:mm:ss");
                dt.setTimeSpec(Qt::UTC);
                currentWeather->lastupdateValue = dt.toLocalTime();
            }
        }
    }
    if (!xml.hasError()) { // Сюда добавится обработка ошибок
        return true;
    } else {
        return false;
    }
}

bool WeatherManager::parseForecastXml(const QByteArray &xmlData, Forecast *forecast) {
    // TODO: Сделать проверки на существование всех элементов и атрибутов, на правильность структуры, на корректность значений; менять объект только в случае успеха.

//    forecastModel->raiseLayoutAboutToBeChanged();

    forecast->clear();

    QXmlStreamReader xml(xmlData);
    bool ok = true;
    while (!xml.atEnd()) {
        xml.readNext();
        if (xml.isStartElement()) {
            if (xml.name() == "location") {
                while (!xml.atEnd() && !(xml.isEndElement() && (xml.name() == "location") && xml.attributes().isEmpty())) {
                    xml.readNext();
                    if (xml.isStartElement()) {
                        if (xml.name() == "name") {
                            forecast->locationName = xml.readElementText();
                        } else if (xml.name() == "country") {
                            forecast->locationCountry = xml.readElementText();
                        } else if (xml.name() == "location") {
                            forecast->location.setAltitude(xml.attributes().value("altitude").toDouble(&ok));
                            forecast->location.setLatitude(xml.attributes().value("latitude").toDouble(&ok));
                            forecast->location.setLongitude(xml.attributes().value("longitude").toDouble(&ok));
                        }
                    }
                }
            } else if (xml.name() == "calctime") {
                forecast->metaCalctime = xml.readElementText().toDouble(&ok);
            } else if (xml.name() == "sun") {
                QDateTime dt = QDateTime::fromString(xml.attributes().value("rise").toString(), "yyyy-MM-ddTHH:mm:ss");
                dt.setTimeSpec(Qt::UTC);
                forecast->sunRise = dt.toLocalTime();
                dt = QDateTime::fromString(xml.attributes().value("set").toString(), "yyyy-MM-ddTHH:mm:ss");
                dt.setTimeSpec(Qt::UTC);
                forecast->sunSet = dt.toLocalTime();
            } else if (xml.name() == "forecast") {

//                int forecastIndex = 0;
                while (!xml.atEnd() && !(xml.isEndElement() && (xml.name() == "forecast"))) {
                    xml.readNext();
                    if (xml.isStartElement()) {
                        if (xml.name() == "time") {
                            QDateTime dt = QDateTime::fromString(xml.attributes().value("from").toString(), "yyyy-MM-ddTHH:mm:ss");
                            dt.setTimeSpec(Qt::UTC);
                            forecast->forecastTimeFrom.append(dt.toLocalTime());
                            dt = QDateTime::fromString(xml.attributes().value("to").toString(), "yyyy-MM-ddTHH:mm:ss");
                            dt.setTimeSpec(Qt::UTC);
                            forecast->forecastTimeTo.append(dt.toLocalTime());
                            Weather *weather = new Weather(forecast);
//                            ++forecastIndex;
                            while (!xml.atEnd() && !(xml.isEndElement() && (xml.name() == "time"))) {
                                xml.readNext();
                                if (xml.isStartElement()) {
                                    if (xml.name() == "symbol") {
                                        weather->weatherNumber = xml.attributes().value("number").toInt(&ok);
                                        weather->weatherValue = xml.attributes().value("name").toString();
                                        weather->weatherIcon = xml.attributes().value("var").toString();
                                    } else if (xml.name() == "precipitation") {
                                        if (xml.attributes().isEmpty()) {
                                            weather->precipitationMode = "no";
                                            weather->precipitationValue = 0;
                                        } else {
                                            weather->precipitationMode = xml.attributes().value("type").toString();
                                            weather->precipitationValue = xml.attributes().value("value").toDouble(&ok);
                                        }
                                    } else if (xml.name() == "windDirection") {
                                        weather->windDirectionValue = xml.attributes().value("deg").toDouble(&ok);
                                        weather->windDirectionCode = xml.attributes().value("code").toString();
                                        weather->windDirectionName = xml.attributes().value("name").toString();
                                    } else if (xml.name() == "windSpeed") {
                                        weather->windSpeedValue = xml.attributes().value("mps").toDouble(&ok);
                                        weather->windSpeedName = xml.attributes().value("name").toString();
                                    } else if (xml.name() == "temperature") {
                                        weather->temperatureUnit = xml.attributes().value("unit").toString();
                                        weather->temperatureValue = xml.attributes().value("value").toDouble(&ok);
                                        weather->temperatureMin = xml.attributes().value("min").toDouble(&ok);
                                        weather->temperatureMax = xml.attributes().value("max").toDouble(&ok);
                                    } else if (xml.name() == "pressure") {
                                        weather->pressureUnit = xml.attributes().value("unit").toString();
                                        weather->pressureValue = xml.attributes().value("value").toDouble(&ok);
                                    } else if (xml.name() == "humidity") {
                                        weather->humidityUnit = xml.attributes().value("unit").toString();
                                        weather->humidityValue = xml.attributes().value("value").toDouble(&ok);
                                    } else if (xml.name() == "clouds") {
                                        weather->cloudsName = xml.attributes().value("value").toString();
                                        weather->cloudsValue = xml.attributes().value("all").toDouble(&ok);
                                    }
                                }
                            }
                            forecast->forecastWeather.append(weather);
                        }
                    }
                }
            }
        }
    }

//    forecastModel->rowCount()
//    forecastModel->raiseLayoutChanged();

    if (!xml.hasError()) { // Сюда добавится обработка ошибок
        return true;
    } else {
        return false;
    }
}

Forecast *WeatherManager::getForecast() const {
    return forecast;
}

//void WeatherManager::replyFinished(QNetworkReply *reply) {
//    qDebug() << "received";

//    if (!reply->error()) {

//        parseCurrentWeatherXml(reply->readAll(), currentWeather);

//        emit responseRefresh();

//    } else {
//        // TODO
//    }

//    reply->deleteLater();
//}

void WeatherManager::replyCurrentWeather() {
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (!reply->error()) {
        parseCurrentWeatherXml(reply->readAll(), currentWeather);
        currentWeather->isInit = true;
        emit responseCurrenWeather(false, currentWeather);
        emit currentWeather->updated();
    } else {
        qDebug() << "Network error! " << reply->errorString() << POS;
        emit responseCurrenWeather(true, currentWeather);
    }
    reply->deleteLater();
}

void WeatherManager::replyForecast() {
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (!reply->error()) {
        emit forecastModel->layoutAboutToBeChanged();
        parseForecastXml(reply->readAll(), forecast);
        emit forecastModel->layoutChanged();
        emit responseForecast(false, forecast);
        emit forecast->updated();
    } else {
        qDebug() << "Network error! " << reply->errorString() << POS;
        emit responseForecast(true, forecast);
    }
    reply->deleteLater();
}
