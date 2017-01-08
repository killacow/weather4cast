import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQml 2.2


Column {

    property string locationName: forecast.locationName
    property string locationCountry: forecast.locationCountry

    Text {
        text: "Forecast"
    }

    Text {
        text: "Place: " + locationName + ", " + locationCountry
    }

    ScrollView {

        height: 300

        ListView {
            //width: 100; height: 100
            //        anchors.fill: parent

            model: forecastModel
            delegate: Rectangle {
                height: 200
                width: 200
                Column {

                    Text {
                        text: "From: " + model.forecastTimeFrom.toLocaleString(Qt.locale(), "dd.MM.yyyy hh:mm:ss")
                    }

                    Text {
                        text: "To: " + model.forecastTimeTo.toLocaleString(Qt.locale(), "dd.MM.yyyy hh:mm:ss")
                    }

                    Weather {
                        weatherValue: model.weatherValue
                        weatherIcon: model.weatherIcon
                        temperatureValue: model.temperatureValue
                        temperatureMin: model.temperatureMin
                        temperatureMax: model.temperatureMax
                        windDirectionName: model.windDirectionName
                        windSpeedValue: model.windSpeedValue
                        humidityValue: model.windSpeedValue
                        pressureValue: model.pressureValue
                        precipitationMode: model.precipitationMode
                        precipitationValue: model.precipitationValue
                        cloudsValue: model.cloudsValue
                        cloudsName: model.cloudsName
                    }

                }

            }
        }
    }
}
