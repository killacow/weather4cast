#include "forecastmodel.h"
#include "forecast.h"
#include "weather.h"



/**
 * @brief Класс-модель для списка прогноза погоды.
 * @param forecast Объект прогноза погоды, который необходимо отображать.
 * @param parent Предок согласно объектной иерархии Qt.
 */
ForecastModel::ForecastModel(Forecast *forecast, QObject *parent)
    : QAbstractListModel(parent)
    , forecast(forecast) {

}



/**
 * @brief Возвращает количество элементов (единичных "погод") в прогнозе погоды.
 * @see QAbstractListModel
 */
int ForecastModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()) {
        return 0;
    }
    return forecast->forecastWeather.size();
}



/**
 * @brief Возвращает данные о погоде.
 * @see QAbstractListModel
 */
QVariant ForecastModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }
    int row = index.row();
    if (row >= forecast->forecastWeather.size()) {
        return QVariant();
    }
    Weather *w = forecast->forecastWeather.at(row);
    switch (role) {
    case weatherValueRole:
        return w->weatherValue;
    case weatherIconRole:
        return w->weatherIcon;
    case precipitationModeRole:
        return w->precipitationMode;
    case precipitationValueRole:
        return w->precipitationValue;
    case windDirectionNameRole:
        return w->windDirectionName;
    case windSpeedValueRole:
        return w->windSpeedValue;
    case temperatureValueRole:
        return w->temperatureValue;
    case temperatureMinRole:
        return w->temperatureMin;
    case temperatureMaxRole:
        return w->temperatureMax;
    case pressureValueRole:
        return w->pressureValue;
    case humidityValueRole:
        return w->humidityValue;
    case cloudsValueRole:
        return w->cloudsValue;
    case cloudsNameRole:
        return w->cloudsName;
    case forecastTimeFromRole:
        return forecast->forecastTimeFrom.at(row);
    case forecastTimeToRole:
        return forecast->forecastTimeTo.at(row);
    default:
        return QVariant();
    }
}



/**
 * @brief Формирует список пользовательских ролей данных.
 * @see QAbstractListModel
 */
QHash<int, QByteArray> ForecastModel::roleNames() const {
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[weatherValueRole] = "weatherValue";
    roles[weatherIconRole] = "weatherIcon";
    roles[precipitationModeRole] = "precipitationMode";
    roles[precipitationValueRole] = "precipitationValue";
    roles[windDirectionNameRole] = "windDirectionName";
    roles[windSpeedValueRole] = "windSpeedValue";
    roles[temperatureValueRole] = "temperatureValue";
    roles[temperatureMinRole] = "temperatureMin";
    roles[temperatureMaxRole] = "temperatureMax";
    roles[pressureValueRole] = "pressureValue";
    roles[humidityValueRole] = "humidityValue";
    roles[cloudsValueRole] = "cloudsValue";
    roles[cloudsNameRole] = "cloudsName";
    roles[forecastTimeFromRole] = "forecastTimeFrom";
    roles[forecastTimeToRole] = "forecastTimeTo";
    return roles;
}
