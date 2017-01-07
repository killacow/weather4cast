#ifndef FORECASTMODEL_H
#define FORECASTMODEL_H

#include <QAbstractListModel>
#include <QtGui>

class Forecast;

class ForecastModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        weatherValueRole = Qt::UserRole + 1,
        weatherIconRole,
        precipitationModeRole,
        precipitationValueRole,
        windDirectionNameRole,
        windSpeedValueRole,
        temperatureValueRole,
        temperatureMinRole,
        temperatureMaxRole,
        pressureValueRole,
        humidityValueRole,
        cloudsValueRole,
        cloudsNameRole,

        forecastTimeFromRole,
        forecastTimeToRole
    };

    explicit ForecastModel(Forecast *forecast, QObject *parent = 0);

    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;

    void raiseLayoutAboutToBeChanged();
    void raiseLayoutChanged();

signals:

public slots:

protected:
    Forecast *forecast;
};

#endif // FORECASTMODEL_H
