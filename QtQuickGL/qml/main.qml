import QtQuick 2.2


Rectangle {
    id:bbox
    width: 720
    height: 576
    color: "#88888888"
    Text {
        text: qsTr("Hello World")
        anchors.centerIn: parent
    }
    MouseArea {
        anchors.rightMargin: -52
        anchors.bottomMargin: -28
        anchors.leftMargin: 52
        anchors.topMargin: 28
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }

    Item {
        id: item_opengl
        x: 256
        y: 305
        width: 200
        height: 200
    }
}
