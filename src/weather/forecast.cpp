#include "forecast.h"
#include "weather.h"

Forecast::Forecast(QObject *parent) : QObject(parent) {
    // TODO: init them all!
    isInit = false;
}

void Forecast::clear() {
    isInit = false;
    forecastTimeFrom.clear();
    forecastTimeTo.clear();
    qDeleteAll(forecastWeather);
    forecastWeather.clear();
}
