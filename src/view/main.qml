import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtCharts 2.0

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

//    Forecast {
//        anchors.fill:parent
//    }

    ChartView {
        title: "Line"
        anchors.fill: parent
        antialiasing: true

        LineSeries {
            name: "LineSeries"
            XYPoint { x: 0; y: 0 }
            XYPoint { x: 1.1; y: 2.1 }
            XYPoint { x: 1.9; y: 3.3 }
            XYPoint { x: 2.1; y: 2.1 }
            XYPoint { x: 2.9; y: 4.9 }
            XYPoint { x: 3.4; y: 3.0 }
            XYPoint { x: 4.1; y: 3.3 }
        }
    }

//    PlaceList {
//        anchors.left: map.right
//        anchors.right: parent.right
//        height: parent.height
//    }

}
