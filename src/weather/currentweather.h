#ifndef CURRENTWEATHER_H
#define CURRENTWEATHER_H

#include <QGeoCoordinate>
#include <QDateTime>
#include "weather.h"

class CurrentWeather : public Weather
{
    Q_OBJECT
    Q_PROPERTY(QString cityName MEMBER cityName NOTIFY updated_inh)
    Q_PROPERTY(QString cityCountry MEMBER cityCountry NOTIFY updated_inh)
    Q_PROPERTY(QDateTime citySunRise MEMBER citySunRise NOTIFY updated_inh)
    Q_PROPERTY(QDateTime citySunSet MEMBER citySunSet NOTIFY updated_inh)
    Q_PROPERTY(double visibilityValue MEMBER visibilityValue NOTIFY updated_inh)
    Q_PROPERTY(QDateTime lastupdateValue MEMBER lastupdateValue NOTIFY updated_inh)
public:
    explicit CurrentWeather(QObject *parent = 0);

    int cityId;
    QString cityName;
    QGeoCoordinate cityCoord;
    QString cityCountry;
    QDateTime citySunRise;
    QDateTime citySunSet;

    double visibilityValue;

    QDateTime lastupdateValue;

signals:
    void updated_inh();
};

#endif // CURRENTWEATHER_H
