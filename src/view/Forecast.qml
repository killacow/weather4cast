import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQml 2.2
import QtQuick.Layouts 1.3


GroupBox {
    title: "Forecast: " + locationName + ", " + locationCountry

    property string locationName: forecast.locationName
    property string locationCountry: forecast.locationCountry

    Layout.fillHeight: true
    Layout.fillWidth: true

    ColumnLayout {

        anchors.fill: parent

        ScrollView {
            Layout.fillHeight: true
            Layout.fillWidth: true
            ListView {
                //                anchors.fill: parent
                model: forecastModel
                delegate:
                    //                    GroupBox {

//                    ColumnLayout {
//                    anchors.fill: parent

                    Weather {
                        title: model.forecastTimeFrom.toLocaleString(Qt.locale(), "dd.MM.yyyy hh:mm") + " - " + model.forecastTimeTo.toLocaleString(Qt.locale(), "dd.MM.yyyy hh:mm") + "   "
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
//                }
            }
        }
    }
}
