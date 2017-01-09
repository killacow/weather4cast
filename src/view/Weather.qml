import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.2

/**
 * Объект, отображающий погоду.
 */
GroupBox {
    title: "Weather"
    property string weatherValue: ""
    property string weatherIcon: ""
    property double temperatureValue: 0
    property double temperatureMin: 0
    property double temperatureMax: 0
    property string windDirectionName: ""
    property double windSpeedValue: 0
    property double humidityValue: 0
    property double pressureValue: 0
    property string precipitationMode: ""
    property double precipitationValue: 0
    property double cloudsValue: 0
    property string cloudsName: ""
    ColumnLayout {
        anchors.fill: parent
        // TODO: Добавить единицы измерения из XML
        Image {
            id: image
            source: weatherIcon.length > 0 ? "http://openweathermap.org/img/w/" + weatherIcon + ".png" : ""
        }
        Text {
            text: "Weather condition: " + weatherValue
        }
        Text {
            function sign(d) {
                if (d > 0) {
                    return "+" + d
                } else {
                    return d
                }
            }
            text: "Temperature: " + sign(temperatureValue.toFixed(0)) + " °C (" + sign(temperatureMin.toFixed(0)) + "..." + sign(temperatureMax.toFixed(0)) + ")"
        }
        Text {
            text: "Wind: " + windDirectionName + ", " + windSpeedValue.toFixed(0) + " mps"
        }
        Text {
            text: "Humidity: " + humidityValue.toFixed(0) + "%"
        }
        Text {
            text: "Pressure: " + pressureValue.toFixed(0) + " hPa"
        }
        Text {
            text: "Precipitation: " + precipitationMode + ((precipitationMode == "no") ? "" : ((precipitationValue < 0) ? "" : ", " + precipitationValue.toFixed(0) + " mm"))
        }
        Text {
            text: "Cloudiness: " + cloudsName + ", " + cloudsValue.toFixed(0) + "%"
        }
    }
}
