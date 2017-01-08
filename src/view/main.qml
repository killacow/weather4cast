import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtCharts 2.0
import QtQuick.Layouts 1.3

// TODO: margins

Window {
    visible: true
    width: 1000
    height: 600
    title: qsTr("weather4cast")

    RowLayout {
        anchors.fill: parent

        ColumnLayout {

            CurrentWeather {
                Layout.fillWidth: true
            }

            Forecast {
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }

        PlaceList {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Map {
            Layout.minimumWidth: 400
            Layout.fillWidth: true
            Layout.fillHeight: true
        }



    }
}
