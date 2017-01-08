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
    Q_PROPERTY(QString locationName MEMBER locationName NOTIFY updated)
    Q_PROPERTY(QString locationCountry MEMBER locationCountry NOTIFY updated)
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

signals:
    void updated();
};

#endif // FORECAST_H
