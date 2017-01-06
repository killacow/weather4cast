#include "weather.h"

Weather::Weather(QObject *parent) : QObject(parent) {
    // TODO: init them all!
    isInit = false;
}

Weather::Weather(const Weather &other, QObject *parent) : QObject(parent) {
//    cityId = other.cityId;
//    cityName = other.cityName;
//    cityCoord = other.cityCoord;
//    cityCountry = other.cityCountry;
//    citySunRise = other.citySunRise;
//    citySunSet = other.citySunSet;

    isInit = other.isInit;

    temperatureValue = other.temperatureValue;
    temperatureMin = other.temperatureMin;
    temperatureMax = other.temperatureMax;
    temperatureUnit = other.temperatureUnit;

    humidityValue = other.humidityValue;
    humidityUnit = other.humidityUnit;

    pressureValue = other.pressureValue;
    pressureUnit = other.pressureUnit;

    windSpeedValue = other.windSpeedValue;
    windSpeedName = other.windSpeedName;
//    windGusts = other.windGusts;
    windDirectionValue = other.windDirectionValue;
    windDirectionCode = other.windDirectionCode;
    windDirectionName = other.windDirectionName;

    cloudsValue = other.cloudsValue;
    cloudsName = other.cloudsName;

//    visibilityValue = other.visibilityValue;

    precipitationMode = other.precipitationMode;

    weatherNumber = other.weatherNumber;
    weatherValue = other.weatherValue;
    weatherIcon = other.weatherIcon;

//    lastupdateValue = other.lastupdateValue;
}

Weather &Weather::operator=(const Weather &other) {
//    cityId = other.cityId;
//    cityName = other.cityName;
//    cityCoord = other.cityCoord;
//    cityCountry = other.cityCountry;
//    citySunRise = other.citySunRise;
//    citySunSet = other.citySunSet;

    isInit = other.isInit;

    temperatureValue = other.temperatureValue;
    temperatureMin = other.temperatureMin;
    temperatureMax = other.temperatureMax;
    temperatureUnit = other.temperatureUnit;

    humidityValue = other.humidityValue;
    humidityUnit = other.humidityUnit;

    pressureValue = other.pressureValue;
    pressureUnit = other.pressureUnit;

    windSpeedValue = other.windSpeedValue;
    windSpeedName = other.windSpeedName;
//    windGusts = other.windGusts;
    windDirectionValue = other.windDirectionValue;
    windDirectionCode = other.windDirectionCode;
    windDirectionName = other.windDirectionName;

    cloudsValue = other.cloudsValue;
    cloudsName = other.cloudsName;

//    visibilityValue = other.visibilityValue;

    precipitationMode = other.precipitationMode;

    weatherNumber = other.weatherNumber;
    weatherValue = other.weatherValue;
    weatherIcon = other.weatherIcon;

//    lastupdateValue = other.lastupdateValue;

    return *this;
}
