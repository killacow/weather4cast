#include "currentweather.h"

CurrentWeather::CurrentWeather(QObject *parent) : Weather(parent) {
    connect(this, SIGNAL(updated()), this, SIGNAL(updated_inh())); // http://stackoverflow.com/questions/38039379/workaround-to-q-property-notify-with-inherited-signal
    // TODO: init them all!
    //isInit = false;
}
