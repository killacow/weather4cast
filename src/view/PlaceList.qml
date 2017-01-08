import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3


// FIXME: Добавить поле поиска/фильтра


GroupBox {
    title: "Places"
    ColumnLayout {
        anchors.fill: parent

        TextField {
            Layout.fillWidth: true
            placeholderText: qsTr("Search")
            onTextChanged: {
                list.positionViewAtIndex(placesModel.getIndexByText(text), ListView.Beginning)
            }
        }

        ScrollView {
            Layout.fillHeight: true
            Layout.fillWidth: true
            verticalScrollBarPolicy: Qt.ScrollBarAlwaysOn
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
                        onClicked: {
                            list.currentIndex = index
                            placesModel.selectPlace(list.currentIndex);
                        }
                    }
                }
                highlight: Rectangle {
                    color: "skyblue"
                }
                highlightMoveVelocity: -1
            }
        }
    }
}
