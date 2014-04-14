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
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }
}
