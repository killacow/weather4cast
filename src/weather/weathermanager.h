#ifndef WEATHERMANAGER_H
#define WEATHERMANAGER_H

#include <QObject>
#include <QtNetwork>
#include <QGeoCoordinate>
#include "../location/place.h"

class CurrentWeather;
class Forecast;
class ForecastModel;
class Place;

class WeatherManager : public QObject
{
    Q_OBJECT
public:
    explicit WeatherManager(QObject *parent = 0);

    bool requestCurrenWeather(int cityId);
    bool requestCurrenWeather(const QGeoCoordinate &location);
    static bool parseCurrentWeatherXml(const QByteArray &xmlData, CurrentWeather *currentWeather);
    CurrentWeather *getCurrentWeather() const;

    bool requestForecast(int cityId);
    bool requestForecast(const QGeoCoordinate &location);
    static bool parseForecastXml(const QByteArray &xmlData, Forecast *forecast);
    Forecast *getForecast() const;

    ForecastModel *forecastModel;

signals:
    void responseCurrenWeather(bool errorFlag, CurrentWeather *currentWeather);
    void responseForecast(bool errorFlag, Forecast *forecast);

public slots:
    void currentPlaceUpdated(const Place &currentPlace);

protected:
    Place currentPlace;
    CurrentWeather *currentWeather;
    Forecast *forecast;
    QNetworkAccessManager *networkAccessManager;
    void timerEvent(QTimerEvent *event);

protected slots:
    void replyCurrentWeather();
    void replyForecast();
};

#endif // WEATHERMANAGER_H
