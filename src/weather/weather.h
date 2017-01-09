#ifndef WEATHER_H
#define WEATHER_H

#include <QObject>

class Weather : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString weatherValue MEMBER weatherValue NOTIFY updated)
    Q_PROPERTY(QString weatherIcon MEMBER weatherIcon NOTIFY updated)
    Q_PROPERTY(QString precipitationMode MEMBER precipitationMode NOTIFY updated)
    Q_PROPERTY(double precipitationValue MEMBER precipitationValue NOTIFY updated)
    Q_PROPERTY(QString windDirectionName MEMBER windDirectionName NOTIFY updated)
    Q_PROPERTY(double windSpeedValue MEMBER windSpeedValue NOTIFY updated)
    Q_PROPERTY(double temperatureValue MEMBER temperatureValue NOTIFY updated)
    Q_PROPERTY(double temperatureMin MEMBER temperatureMin NOTIFY updated)
    Q_PROPERTY(double temperatureMax MEMBER temperatureMax NOTIFY updated)
    Q_PROPERTY(double pressureValue MEMBER pressureValue NOTIFY updated)
    Q_PROPERTY(double humidityValue MEMBER humidityValue NOTIFY updated)
    Q_PROPERTY(double cloudsValue MEMBER cloudsValue NOTIFY updated)
    Q_PROPERTY(QString cloudsName MEMBER cloudsName NOTIFY updated)
public:
    explicit Weather(QObject *parent = 0);

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

signals:
    void updated();
};

#endif // WEATHER_H
