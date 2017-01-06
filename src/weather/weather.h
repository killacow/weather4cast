#ifndef WEATHER_H
#define WEATHER_H

#include <QObject>

// TODO: сделать все поля private

class Weather : public QObject
{
    Q_OBJECT
public:
    explicit Weather(QObject *parent = 0);
    explicit Weather(const Weather &other, QObject *parent = 0);
    Weather &operator=(const Weather &other);

    bool isInit;

    int weatherNumber;
    QString weatherValue;
    QString weatherIcon;

    QString precipitationMode;
    double precipitationValue;

    double windDirectionValue;
    QString windDirectionCode;
    QString windDirectionName;

    double windSpeedValue;
    QString windSpeedName;

    double temperatureValue;
    double temperatureMin;
    double temperatureMax;
    QString temperatureUnit;

    double pressureValue;
    QString pressureUnit;

    double humidityValue;
    QString humidityUnit;

    double cloudsValue;
    QString cloudsName;




//    QString cityName;
//    QGeoCoordinate cityCoord;
//    QString cityCountry;

//    QDateTime citySunRise;
//    QDateTime citySunSet;




//    int cityId;
//    double visibilityValue;
//    QDateTime lastupdateValue;


};

#endif // WEATHER_H
