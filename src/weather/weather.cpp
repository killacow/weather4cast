#include "weather.h"

Weather::Weather(QObject *parent) : QObject(parent) {
    //    isInit = false;

    weatherNumber = 0;
    precipitationValue = 0;
    windDirectionValue = 0;
    windSpeedValue = 0;
    temperatureValue = 0;
    temperatureMin = 0;
    temperatureMax = 0;
    pressureValue = 0;
    humidityValue = 0;
    cloudsValue = 0;
}
