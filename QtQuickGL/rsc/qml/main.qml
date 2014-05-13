import QtQuick 2.0
import OpenGLUnderQML 1.0

Item {
    id: item1

    width: 320
    height: 480

    WindowGL {
        id: window
    }

    Rectangle {
        color: Qt.rgba(0, 0, 0, 0.5)
        radius: 10
        border.width: 1
        border.color: "white"
        anchors.fill: label
        anchors.margins: -10
    }

    Text {
        id: label
        color: "white"
        wrapMode: Text.WordWrap
        text: "The background here is rendered with raw OpenGL using the 'beforeRender()' signal in QQuickWindow. This text label and its border is rendered using QML"
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.margins: 20
    }

    Text {
        id: text1
        x: 75
        y: 238
        width: 68
        height: 47
        text: qsTr("Das ist text")
        wrapMode: Text.NoWrap
        font.pixelSize: 12
    }

    MouseArea {
        id: mouseArea1
        anchors.fill: parent

        onClicked: {
            console.log("mouse clicked")
            if (mouse.button == Qt.RightButton) {

            glObject.changeAngle()
            }
        }

        onWheel: {
            console.log("on wheel")
            if (wheel.angleDelta.y != 0)
                console.log("change distance")
            glObject.changeDistance(wheel.angleDelta.y);
        }
        onDoubleClicked: {
            console.log("quit")
            Qt.quit()
        }

    }
}
