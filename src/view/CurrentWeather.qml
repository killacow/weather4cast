import QtQuick 2.0
import QtQml 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.2

GroupBox {
    title: "Current weather"

    property string cityName: currentWeather.cityName
    property string cityCountry: currentWeather.cityCountry
    property date citySunRise: currentWeather.citySunRise
    property date citySunSet: currentWeather.citySunSet
    property double visibilityValue: currentWeather.visibilityValue
    property date lastupdateValue: currentWeather.lastupdateValue

//    Layout.fillWidth: true
//    Layout.fillHeight: true

    ColumnLayout {



        anchors.fill: parent

        Text {
            text: "Place: " + cityName + ", " + cityCountry
        }

        Text {
            text: "Sunrise time: " + citySunRise.toLocaleString(Qt.locale(), "dd.MM.yyyy hh:mm:ss")
        }

        Text {
            text: "Sunset  time: " + citySunSet.toLocaleString(Qt.locale(), "dd.MM.yyyy hh:mm:ss")
        }

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
            text: "Visibility: " + visibilityValue.toFixed(0) + " m"
        }

        Text {
            text: "Last update: " + lastupdateValue.toLocaleString(Qt.locale(), "dd.MM.yyyy hh:mm:ss")
        }

    }
}
