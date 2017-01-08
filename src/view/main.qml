import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtWebEngine 1.0

// TODO: margins

Window {
    visible: true
    width: 1200
    height: 800
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
