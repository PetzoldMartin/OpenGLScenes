import QtQuick 2.2
import OpenGLUnderQML 1.0
import QtQuick.Controls 1.1
//import "CreateTab.qml"


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

        Timer {
            interval: 1000/60; running: true; repeat: true
            //onTriggered: window.update() // SEGMENTAITION FAULT
        }


        Keys.onPressed: {
            switch(event.key) {
            case Qt.Key_F1:
                window.setViewMode(0)
                break
            case Qt.Key_F2:
                window.setViewMode(1)
                break
            case Qt.Key_F3:
                window.setViewMode(2)
                break
            case Qt.Key_F4:
                window.setViewMode(3)
                break
            case Qt.Key_F5:
                window.setViewMode(4)
                break
            }
        }
    }

    MouseArea {
        id: mouseListenerArea
        anchors.fill: parent
        acceptedButtons: Qt.AllButtons;


        //        onClicked: {
        //            console.log("left button: " + mouse.x + "\t" + mouse.y)
        //            console.log("Delta Mouse: "+ (mouse.x-window.mouseX) + "\t" + (mouse.y-window.mouseY))
        //            window.rotateView(window.selectedObjectId,mouse.x-window.mouseX,mouse.y-window.mouseY)
        //        }


        onMouseXChanged: {
            console.log("DeltaX Mouse: "+ (mouse.x-window.mouseX))
            window.rotateView(mouse.x-window.mouseX,0)
            window.setMousePose(mouse.x, mouse.y)   // for hover pick
            window.mouseX=mouse.x
        }

        onMouseYChanged:  {
            console.log("DeltaY Mouse: "+ (mouse.y-window.mouseY))
            window.rotateView(0,mouse.y-window.mouseY)
            window.setMousePose(mouse.x, mouse.y)  // for hover pick
            window.mouseY=mouse.y
        }

        onPressed: {
            console.log("mousePressed");
            window.mouseX=mouse.x
            window.mouseY=mouse.y
            if (mouse.button == Qt.RightButton){
                console.log("Object Menu")
                window.toggleRenderMode();
            }
        }

        onReleased: {
            //TODO
        }

        onDoubleClicked: {
            window.selectedObjectId = window.pickObjectAt()
        }

        onWheel: {
            if (wheel.angleDelta.y != 0) {
                console.log("wheel event: " + wheel.angleDelta.y)
                window.scaleView(wheel.angleDelta.y)
            }

        }

        // Options

        Item {
            id: options

            Rectangle {
                id: menu
                width: 0
                height: mainItem.height
                color: Qt.rgba(0, 0, 0, 0.5)
                anchors.left: parent.left

                property int widthOpen: 260

                // Toggle to open and close the menu
                ToggleOptions{
                    onTurnOff: menu.close()
                    onTurnOn: menu.open()
                }


                // TODO create Buttons

                Rectangle {
                    id: modi
                    width: parent.width
                    anchors.left: parent.left
                    anchors.top: parent.top
                    anchors.topMargin: 20
                    visible: false

                    Row {
                        id: row
                        anchors.left: parent.left
                        anchors.verticalCenter: parent.verticalCenter
                        layer.enabled: true
                        spacing: 5

                        Rectangle { width: 32; height: 32; color: Qt.rgba(0, 0, 0, 0) }

                        Button { text: "create"; onClicked: menu.tapChange(1) }

                        Button { text: "delete"; onClicked: menu.tapChange(2) }

                        Button { text: "modify"; onClicked: menu.tapChange(3) }

                    }

                    CreateTab { id: createOptions; anchors.top: row.bottom }
                    ModifyTab { id: modifyOptions; anchors.top: row.bottom }

                }

                function tapChange(tap) {
                    switch(tap) {
                    case 1: // Show Create Options
                        createOptions.visible = true
                        modifyOptions.visible = false
                        break
                    case 2: // Show Delete Options
                        createOptions.visible = false
                        modifyOptions.visible = false
                        break
                    case 3: // Show Modify Options
                        createOptions.visible = false
                        modifyOptions.visible = true
                        break
                    default: break
                    }
                }

                function open() {
                    width = widthOpen
                    modi.visible = true
                }

                function close() {
                    width = 0
                    modi.visible = false
                }
            }

        }

    }

}
