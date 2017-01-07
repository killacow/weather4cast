import QtQuick 2.7
import QtQuick.Controls 1.4

// FIXME: Добавить поле поиска/фильтра

ScrollView {
    ListView {
        id: list
        anchors.fill: parent
        model: placesModel
        delegate: Item {
            width: list.width
            height: 20
            Text {
                anchors.verticalCenter: parent.verticalCenter
                text: display
            }
            MouseArea {
                anchors.fill: parent
                onClicked: list.currentIndex = index
            }
        }
        highlight: Rectangle {
            color: "skyblue"
        }
        highlightMoveVelocity: -1
        onCurrentItemChanged: {
//            console.log(list.currentIndex + ' selected')
            placesModel.selectPlace(list.currentIndex);
        }
    }
}
