#ifndef FORECAST_H
#define FORECAST_H

#include <QObject>
#include <QGeoCoordinate>
#include <QDateTime>
#include <QVector>

class Weather;

class Forecast : public QObject
{
    Q_OBJECT
public:
    explicit Forecast(QObject *parent = 0);

    void clear();

    bool isInit;

    QString locationName;
    QString locationCountry;
    QGeoCoordinate location;

    double metaCalctime;

    QDateTime sunRise;
    QDateTime sunSet;

    QList<QDateTime> forecastTimeFrom;
    QList<QDateTime> forecastTimeTo;
    QList<Weather *> forecastWeather;

};

#endif // FORECAST_H
