import QtQuick 2.0
import OpenGLUnderQML 1.0

Item {
    id: mainItem

    width: 600
    height: 480

    WindowGL {
        id: window
        focus: true
        property int mouseX: 0
        property int mouseY: 0
        property int selectedObjectId: 0


        Keys.onPressed: {
            switch(event.key) {
                case Qt.Key_F1:
                    window.setViewMode(0)
                    break
                case Qt.Key_F2:
                    window.setViewMode(1)
                    break
            }
            window.update()
        }
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

    MouseArea {
        id: mouseListenerArea
        anchors.fill: parent

        //        onClicked: {
        //            console.log("left button: " + mouse.x + "\t" + mouse.y)
        //            console.log("Delta Mouse: "+ (mouse.x-window.mouseX) + "\t" + (mouse.y-window.mouseY))
        //            window.rotateView(window.selectedObjectId,mouse.x-window.mouseX,mouse.y-window.mouseY)
        //        }


        onMouseXChanged: {
            console.log("DeltaX Mouse: "+ (mouse.x-window.mouseX))
            window.rotateView(mouse.x-window.mouseX,0)
            window.mouseX=mouse.x
            window.update()
        }

        onMouseYChanged:  {
            console.log("DeltaY Mouse: "+ (mouse.y-window.mouseY))
            window.rotateView(0,mouse.y-window.mouseY)
            window.mouseY=mouse.y
            window.update()
        }

        onPressed: {
            window.selectedObjectId = window.pickObjectAt(mouse.x,mouse.y)
            window.mouseX=mouse.x
            window.mouseY=mouse.y
            window.update()
        }

        onReleased: {
            //TODO
        }

        onDoubleClicked: {
            console.log("quit")
            Qt.quit()
        }

        onWheel: {
            if (wheel.angleDelta.y != 0) {
                console.log("wheel event: " + wheel.angleDelta.y)
                window.scaleView(window.selectedObjectId, wheel.angleDelta.y)
                window.update()
            }
        }
    }
}
