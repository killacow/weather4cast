import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("weather4cast") // TODO: Ярлык

    Map {
        id: map
        width: 300
        anchors.left: parent.left
        height: parent.height
    }

//    ComboBox {
//        model: placesModel
//        textRole: "display"
//    }

    PlaceList {
        anchors.left: map.right
        height: parent.height
//        anchors.fill: parent
    }

}
