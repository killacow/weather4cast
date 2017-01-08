#include "currentweather.h"

CurrentWeather::CurrentWeather(QObject *parent) : Weather(parent) {
    connect(this, SIGNAL(updated()), this, SIGNAL(updated_inh())); // http://stackoverflow.com/questions/38039379/workaround-to-q-property-notify-with-inherited-signal
    //isInit = false;
    cityId = 0;
    visibilityValue = 0;
}
