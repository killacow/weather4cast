import QtQuick 2.5

//Item {



//    height: 200
//    width: 200

    Column {

        // TODO: Добавить единицы измерения из XML

        property bool isInit: true

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

        //opacity: (isInit == true) ? 1 : 0

        Image {
            id: image
            source: weatherIcon.length > 0 ? "http://openweathermap.org/img/w/" + weatherIcon + ".png" : ""
            width: 50
            height: 50
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
            text: "Temperature: " + sign(temperatureValue.toFixed(0)) + " ℃ (" + sign(temperatureMin.toFixed(0)) + "..." + sign(temperatureMax.toFixed(0)) + ")" // TODO: Кривое отображение символа градуса
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
            text: "Precipitation: " + precipitationMode + ((precipitationMode == "no") ? "" : ", " + precipitationValue.toFixed(0) + " mm")
        }

        Text {
            text: "Cloudiness: " + cloudsName + ", " + cloudsValue.toFixed(0) + "%"
        }

    }
//}
