#include "forecast.h"
#include "weather.h"

Forecast::Forecast(QObject *parent) : QObject(parent) {
//    isInit = false;
    metaCalctime = 0;
}

void Forecast::clear() {
//    isInit = false;
    forecastTimeFrom.clear();
    forecastTimeTo.clear();
    qDeleteAll(forecastWeather);
    forecastWeather.clear();
}
