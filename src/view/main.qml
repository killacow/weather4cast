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
    title: qsTr("weather4cast") // TODO: Ярлык

    RowLayout {
        anchors.fill: parent

        ColumnLayout {
//            anchors.fill: parent

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

//    Map {
//        id: map
//        width: 500
//        anchors.left: parent.left
//        height: parent.height
//    }

//    PlaceList {
//        anchors.left: map.right
//        anchors.right: parent.right
//        height: parent.height
//    }


    //    ChartView {
    //        title: "Line"
    //        anchors.fill: parent
    //        antialiasing: true

    //        LineSeries {
    //            name: "LineSeries"
    //            XYPoint { x: 0; y: 0 }
    //            XYPoint { x: 1.1; y: 2.1 }
    //            XYPoint { x: 1.9; y: 3.3 }
    //            XYPoint { x: 2.1; y: 2.1 }
    //            XYPoint { x: 2.9; y: 4.9 }
    //            XYPoint { x: 3.4; y: 3.0 }
    //            XYPoint { x: 4.1; y: 3.3 }
    //        }
    //    }



}
