#include "currentweather.h"

CurrentWeather::CurrentWeather(QObject *parent) : Weather(parent) {
    // TODO: init them all!
    isInit = false;
}

CurrentWeather::CurrentWeather(const CurrentWeather &other, QObject *parent) : Weather(other, parent) {

    isInit = other.isInit;

    cityId = other.cityId;
    cityName = other.cityName;
    cityCoord = other.cityCoord;
    cityCountry = other.cityCountry;
    citySunRise = other.citySunRise;
    citySunSet = other.citySunSet;

//    temperatureValue = other.temperatureValue;
//    temperatureMin = other.temperatureMin;
//    temperatureMax = other.temperatureMax;
//    temperatureUnit = other.temperatureUnit;

//    humidityValue = other.humidityValue;
//    humidityUnit = other.humidityUnit;

//    pressureValue = other.pressureValue;
//    pressureUnit = other.pressureUnit;

//    windSpeedValue = other.windSpeedValue;
//    windSpeedName = other.windSpeedName;
//    windGusts = other.windGusts;
//    windDirectionValue = other.windDirectionValue;
//    windDirectionCode = other.windDirectionCode;
//    windDirectionName = other.windDirectionName;

//    cloudsValue = other.cloudsValue;
//    cloudsName = other.cloudsName;

    visibilityValue = other.visibilityValue;

//    precipitationMode = other.precipitationMode;

//    weatherNumber = other.weatherNumber;
//    weatherValue = other.weatherValue;
//    weatherIcon = other.weatherIcon;

    lastupdateValue = other.lastupdateValue;
}

CurrentWeather &CurrentWeather::operator=(const CurrentWeather &other) {

    Weather::operator=(other);

    isInit = other.isInit;

    cityId = other.cityId;
    cityName = other.cityName;
    cityCoord = other.cityCoord;
    cityCountry = other.cityCountry;
    citySunRise = other.citySunRise;
    citySunSet = other.citySunSet;

//    temperatureValue = other.temperatureValue;
//    temperatureMin = other.temperatureMin;
//    temperatureMax = other.temperatureMax;
//    temperatureUnit = other.temperatureUnit;

//    humidityValue = other.humidityValue;
//    humidityUnit = other.humidityUnit;

//    pressureValue = other.pressureValue;
//    pressureUnit = other.pressureUnit;

//    windSpeedValue = other.windSpeedValue;
//    windSpeedName = other.windSpeedName;
//    windGusts = other.windGusts;
//    windDirectionValue = other.windDirectionValue;
//    windDirectionCode = other.windDirectionCode;
//    windDirectionName = other.windDirectionName;

//    cloudsValue = other.cloudsValue;
//    cloudsName = other.cloudsName;

    visibilityValue = other.visibilityValue;

//    precipitationMode = other.precipitationMode;

//    weatherNumber = other.weatherNumber;
//    weatherValue = other.weatherValue;
//    weatherIcon = other.weatherIcon;

    lastupdateValue = other.lastupdateValue;

    return *this;
}
