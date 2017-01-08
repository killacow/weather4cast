import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3


// FIXME: Добавить поле поиска/фильтра


GroupBox {
    title: "Places"
    ScrollView {
        anchors.fill: parent
        ListView {
            id: list
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
                placesModel.selectPlace(list.currentIndex);
            }
        }
    }
}
