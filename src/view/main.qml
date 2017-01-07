import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("weather4cast") // TODO: Ярлык

//    Map {
//        id: map
//        width: 500
//        anchors.left: parent.left
//        height: parent.height
//    }

//    CurrentWeather {
//        anchors.fill: parent
//    }

    Forecast {
        anchors.fill:parent
    }

//    PlaceList {
//        anchors.left: map.right
//        anchors.right: parent.right
//        height: parent.height
//    }

}
