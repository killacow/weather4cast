#ifndef CURRENTWEATHER_H
#define CURRENTWEATHER_H

#include <QGeoCoordinate>
#include <QDateTime>
#include "weather.h"

// TODO: Сделать нормальные геттеры/сеттеры для полей.

class CurrentWeather : public Weather
{
    Q_OBJECT
public:
    explicit CurrentWeather(QObject *parent = 0);
    explicit CurrentWeather(const CurrentWeather &other, QObject *parent = 0);
    CurrentWeather &operator=(const CurrentWeather &other);

    bool isInit;

    int cityId;
    QString cityName;
    QGeoCoordinate cityCoord;
    QString cityCountry;
    QDateTime citySunRise;
    QDateTime citySunSet;

//    double temperatureValue;
//    double temperatureMin;
//    double temperatureMax;
//    QString temperatureUnit;

//    double humidityValue;
//    QString humidityUnit;

//    double pressureValue;
//    QString pressureUnit;

//    double windSpeedValue;
//    QString windSpeedName;
//    bool windGusts;                 // TODO: windGusts
//    double windDirectionValue;
//    QString windDirectionCode;
//    QString windDirectionName;

//    double cloudsValue;
//    QString cloudsName;

    double visibilityValue;

//    QString precipitationMode;

//    int weatherNumber;
//    QString weatherValue;
//    QString weatherIcon;

    QDateTime lastupdateValue;

};

#endif // CURRENTWEATHER_H
