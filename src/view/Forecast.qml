import QtQuick 2.0

Item {
    // https://habrahabr.ru/post/184416/
    ListView {
        //width: 100; height: 100
        anchors.fill: parent

        model: cppListModel
        delegate: Rectangle {
            height: 25
            width: 100
            color: model.color
            Text { text: model.text }
        }
    }
}
