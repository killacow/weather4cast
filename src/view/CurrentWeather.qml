import QtQuick 2.0
import QtQml 2.2

Item {
    property string cityName: currentWeather.cityName
    property string cityCountry: currentWeather.cityCountry
//    property date citySunRise: currentWeather.citySunRise
//    property date citySunSet: new Date()
    property double visibilityValue: currentWeather.visibilityValue
//    property date lastupdateValue: new Date()

    Column {

        Text {
            text: "Place: " + cityName + ", " + cityCountry
        }

//        Text {
//            text: "Sunrise time " + citySunRise.toLocaleString(Qt.locale(), "dd.MM.yyyy hh:mm:ss")
//        }

//        Text {
////            text: "Sunset  time " + citySunSet
//        }



//        Text {
////            text: "Last update " + lastupdateValue
//        }

        Weather {
//            isInit: currentWeather.isInit
            weatherValue: currentWeather.weatherValue
            weatherIcon: currentWeather.weatherIcon
            temperatureValue: currentWeather.temperatureValue
            temperatureMin: currentWeather.temperatureMin
            temperatureMax: currentWeather.temperatureMax
            windDirectionName: currentWeather.windDirectionName
            windSpeedValue: currentWeather.windSpeedValue
            humidityValue: currentWeather.windSpeedValue
            pressureValue: currentWeather.pressureValue
            precipitationMode: currentWeather.precipitationMode
            precipitationValue: currentWeather.precipitationValue
            cloudsValue: currentWeather.cloudsValue
            cloudsName: currentWeather.cloudsName
        }

        Text {
            text: "Visibility " + visibilityValue.toFixed(0) + " m"
        }

    }
}
