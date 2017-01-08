import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3

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
                            if (list.currentIndex == index) { // Для того чтобы обновлять местоположение даже если Пользователь кликнул по уже выбранному пункту
                                placesModel.selectPlace(list.currentIndex);
                            }
                            list.currentIndex = index
                        }
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
}
