#include "weathermanager.h"
#include "weather.h"
#include "currentweather.h"
#include "forecast.h"
#include "forecastmodel.h"
#include "../utils.h"
#include "../location/place.h"
#include "../location/locationmanager.h"
#include "../settings.h"

// TODO: По всему проекту сделать нормальные геттеры/сеттеры для полей, сами поля приватными.



/**
 * @brief Класс - менеджер погоды.
 * @param parent Предок согласно объектной иерархии Qt.
 */
WeatherManager::WeatherManager(QObject *parent) : QObject(parent) {
    networkAccessManager = new QNetworkAccessManager(this);
    currentWeather = new CurrentWeather(this);
    forecast = new Forecast(this);
    forecastModel = new ForecastModel(forecast, this);
    // TODO: Таймер на обновление погоды лучше заводить каждый раз после обновления.
    startTimer(Settings::getInstance()->value("refreshPeriodSec").toInt() * 1000); // Обновление погоды.
}



/**
 * @return Текущую погоду.
 */
CurrentWeather *WeatherManager::getCurrentWeather() const {
    return currentWeather;
}



/**
 * @brief Слот-обработчик сигнала об обновлени местоположения.
 * @param currentPlace Текущее местоположение.
 */
void WeatherManager::currentPlaceUpdated(const Place &currentPlace) {
    this->currentPlace = currentPlace;
    if (currentPlace.id == LocationManager::autoLocation) {
        requestCurrenWeather(currentPlace.coordinate);
        requestForecast(currentPlace.coordinate);
    } else {
        requestCurrenWeather(currentPlace.id);
        requestForecast(currentPlace.id);
    }
}



/**
 * @brief Обработчик срабатывания таймера.
 * Используется для обновления погоды через заданный промежуток времени.
 * @param event @see QTimerEvent.
 */
void WeatherManager::timerEvent(QTimerEvent *event) {
    Q_UNUSED(event);
    currentPlaceUpdated(currentPlace);
}



/**
 * @brief Инициирует обновление информации о текущей погоде в месте, соответствующем идентификатору id из JSON-файла.
 * @param cityId id из JSON-файла.
 * @return Успешно ли прошла инициализация.
 */
bool WeatherManager::requestCurrenWeather(int cityId) {
    if (false) { // TODO: Проверить на слишком высокую частоту запросов, проверить на корректность местоположения.
        return false;
    }
    QUrl address = QString("http://api.openweathermap.org/data/2.5/weather?id=%1&units=metric&mode=xml&appid=%2")
            .arg(QString::number(cityId)).arg(Settings::getInstance()->value("openweathermapAppid").toString());
    QNetworkReply *reply = networkAccessManager->get(QNetworkRequest(QUrl(address)));
    connect(reply, SIGNAL(finished()), this, SLOT(replyCurrentWeather()));
    return true;
}



/**
 * @brief Инициирует обновление информации о текущей погоде.
 * @param location Координаты места.
 * @return Успешно ли прошла инициализация.
 */
bool WeatherManager::requestCurrenWeather(const QGeoCoordinate &location) {
    if (false) { // TODO: Проверить на слишком высокую частоту запросов, проверить на корректность местоположения.
        return false;
    }
    QUrl address = QString("http://api.openweathermap.org/data/2.5/weather?lat=%1&lon=%2&units=metric&mode=xml&appid=%3")
            .arg(QString::number(location.latitude(), 'f'))
            .arg(QString::number(location.longitude(), 'f'))
            .arg(Settings::getInstance()->value("openweathermapAppid").toString());
    QNetworkReply *reply = networkAccessManager->get(QNetworkRequest(QUrl(address)));
    connect(reply, SIGNAL(finished()), this, SLOT(replyCurrentWeather()));
    return true;
}



/**
 * @brief Инициирует обновление информации о прогнозе погоды в месте, соответствующем идентификатору id из JSON-файла.
 * @param cityId id из JSON-файла.
 * @return Успешно ли прошла инициализация.
 */
bool WeatherManager::requestForecast(int cityId) {
    if (false) { // TODO: Проверить на слишком высокую частоту запросов, проверить на корректность местоположения.
        return false;
    }
    QUrl address = QString("http://api.openweathermap.org/data/2.5/forecast?id=%1&units=metric&mode=xml&appid=%2")
            .arg(QString::number(cityId))
            .arg(Settings::getInstance()->value("openweathermapAppid").toString());
    QNetworkReply *reply = networkAccessManager->get(QNetworkRequest(QUrl(address)));
    connect(reply, SIGNAL(finished()), this, SLOT(replyForecast()));
    return true;
}



/**
 * @brief Инициирует обновление информации о прогнозе погоды.
 * @param location Координаты места.
 * @return Успешно ли прошла инициализация.
 */
bool WeatherManager::requestForecast(const QGeoCoordinate &location) {
    if (false) { // TODO: Проверить на слишком высокую частоту запросов, проверить на корректность местоположения.
        return false;
    }
    QUrl address = QString("http://api.openweathermap.org/data/2.5/forecast?lat=%1&lon=%2&units=metric&mode=xml&appid=%3")
            .arg(QString::number(location.latitude(), 'f'))
            .arg(QString::number(location.longitude(), 'f'))
            .arg(Settings::getInstance()->value("openweathermapAppid").toString());
    QNetworkReply *reply = networkAccessManager->get(QNetworkRequest(QUrl(address)));
    connect(reply, SIGNAL(finished()), this, SLOT(replyForecast()));
    return true;
}



/**
 * @brief Разбирает XML-данные о текущей погоде.
 * @param xmlData Данные.
 * @param[out] currentWeather Объект, в который будут записаны данные о текущей погоде.
 * @return Успех/неуспех.
 */
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
                currentWeather->precipitationValue = xml.attributes().value("value").toDouble(&ok);
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



/**
 * @brief Разбирает XML-данные о прогнозе погоды.
 * @param xmlData Данные.
 * @param[out] forecast Объект, в который будут записаны данные о прогнозе погоды.
 * @return Успех/неуспех.
 */
bool WeatherManager::parseForecastXml(const QByteArray &xmlData, Forecast *forecast) {
    // TODO: Сделать проверки на существование всех элементов и атрибутов, на правильность структуры, на корректность значений; менять объект только в случае успеха.
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
    if (!xml.hasError()) { // Сюда добавится обработка ошибок
        return true;
    } else {
        return false;
    }
}



/**
 * @return Прогноз погоды.
 */
Forecast *WeatherManager::getForecast() const {
    return forecast;
}



/**
 * @brief Слот-обработчик сигнала о поступлении ответа на запрос текущей погоды.
 */
void WeatherManager::replyCurrentWeather() {
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (!reply->error()) {
        parseCurrentWeatherXml(reply->readAll(), currentWeather);
        emit responseCurrenWeather(false, currentWeather);
        emit currentWeather->updated();
    } else {
        emit responseCurrenWeather(true, currentWeather);
    }
    reply->deleteLater();
}



/**
 * @brief Слот-обработчик сигнала о поступлении ответа на запрос прогноза погоды.
 */
void WeatherManager::replyForecast() {
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (!reply->error()) {
        emit forecastModel->layoutAboutToBeChanged();
        parseForecastXml(reply->readAll(), forecast);
        emit forecastModel->layoutChanged();
        emit responseForecast(false, forecast);
        emit forecast->updated();
    } else {
        emit responseForecast(true, forecast);
    }
    reply->deleteLater();
}
