#include "forecast.h"
#include "weather.h"



/**
 * @brief Класс-контейнер, хранящий информацию о т.н. прогнозе погоды на 5 дней (https://openweathermap.org/forecast5).
 * @param parent Предок согласно объектной иерархии Qt.
 */
Forecast::Forecast(QObject *parent) : QObject(parent) {
    metaCalctime = 0;
}



/**
 * @brief Очищает массивы прогнозов.
 */
void Forecast::clear() {
    forecastTimeFrom.clear();
    forecastTimeTo.clear();
    qDeleteAll(forecastWeather);
    forecastWeather.clear();
}
