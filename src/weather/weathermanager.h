#ifndef WEATHERMANAGER_H
#define WEATHERMANAGER_H

#include <QObject>
#include <QtNetwork>
#include <QGeoCoordinate>

class CurrentWeather;
class Forecast;

class WeatherManager : public QObject
{
    Q_OBJECT
public:
    explicit WeatherManager(QObject *parent = 0);

    QGeoCoordinate getLocation() const;
    void setLocation(const QGeoCoordinate &value);

    bool requestCurrenWeather(int cityId);
    bool requestCurrenWeather(const QGeoCoordinate &location);
    static bool parseCurrentWeatherXml(const QByteArray &xmlData, CurrentWeather *currentWeather);
    CurrentWeather *getCurrentWeather() const;

    bool requestForecast(int cityId);
    bool requestForecast(const QGeoCoordinate &location);
    static bool parseForecastXml(const QByteArray &xmlData, Forecast *forecast);
    Forecast *getForecast() const;

    bool requestRefresh();

signals:
    void responseCurrenWeather(bool errorFlag, CurrentWeather *currentWeather);
    void responseForecast(bool errorFlag, Forecast *forecast);

    void responseRefresh();

public slots:

protected:
    QGeoCoordinate location;
    CurrentWeather *currentWeather;
    Forecast *forecast;

    QNetworkAccessManager *networkAccessManager;

protected slots:
    void replyFinished(QNetworkReply *reply);
    void replyCurrentWeather();
    void replyForecast();
};

#endif // WEATHERMANAGER_H
