#include "weather.h"



/**
 * @brief Класс-контейнер, хранящий информацию о погоде.
 * @param parent Предок согласно объектной иерархии Qt.
 */
Weather::Weather(QObject *parent) : QObject(parent) {
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
