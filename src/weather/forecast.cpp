#include "forecast.h"
#include "weather.h"

Forecast::Forecast(QObject *parent) : QObject(parent) {
    // TODO: init them all!

//    int forecastLength = 40; // TODO: Вынести в настройки
//    forecastTimeFrom.resize(forecastLength);
//    forecastTimeTo.resize(forecastLength);
//    forecastWeather.resize(forecastLength);
//    for (int i = 0; i < forecastLength; ++i) {
//        forecastWeather[i] = new Weather(this);
//    }

    isInit = false;
}

void Forecast::clear() {
    isInit = false;
    forecastTimeFrom.clear();
    forecastTimeTo.clear();
    qDeleteAll(forecastWeather);
    forecastWeather.clear();
}
