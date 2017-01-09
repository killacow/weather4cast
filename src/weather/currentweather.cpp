#include "currentweather.h"



/**
 * @brief Класс-контейнер, хранящий информацию о т.н. "текущей погоде" (https://openweathermap.org/current).
 * @param parent Предок согласно объектной иерархии Qt.
 */
CurrentWeather::CurrentWeather(QObject *parent) : Weather(parent) {
    connect(this, SIGNAL(updated()), this, SIGNAL(updated_inh())); // http://stackoverflow.com/questions/38039379/workaround-to-q-property-notify-with-inherited-signal
    cityId = 0;
    visibilityValue = 0;
}
