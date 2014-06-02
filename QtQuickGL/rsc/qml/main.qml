import QtQuick 2.0
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
                toggleOptions.toggleOptions()



            }
        }


        onReleased: {
            //TODO
        }

        onDoubleClicked: {
            window.selectedObjectId = window.pickObjectAt(mouse.x,mouse.y)
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
                    anchors.topMargin: 16
                    anchors.leftMargin: 32
                    visible: false


                    Row {
                        anchors.left: parent.left
                        anchors.verticalCenter: parent.verticalCenter
                        layer.enabled: true
                        spacing: 5

                        Rectangle { color: Qt.rgba(0,0.0,0,0.5)
                            width: 70; height: 20;
                            Text { anchors.centerIn: parent
                                color: "white"
                                font.pointSize: 12; text: "CREATE" } }
                        Rectangle { color: Qt.rgba(0,0.0,0,0.5)
                            width: 70; height: 20
                            Text { anchors.centerIn: parent
                                color: "white"
                                font.pointSize: 12; text: "DELETE" } }
                        Rectangle { color: Qt.rgba(0,0.0,0,0.5)
                                    width: 70; height: 20
                                    Text { anchors.centerIn: parent
                                           color: "white"
                                           font.pointSize: 12; text: "MODIFY" }
                                    function mouseEnterToogleOption() {
                                        color = toggleOptions.colorOnHover

                                    }

                                    function mouseExitedToogleOption() {
                                        color = toggleOptions.colorOffHover
                                    }
                                    MouseArea {
                                        anchors.fill: parent
                                        hoverEnabled: true
                                        onEntered: parent.mouseEnterToogleOption()
                                        onExited: parent.mouseExitedToogleOption()
                                        onClicked: modifyOptions.toggleOptions()
                                    }

                        }

                    }

                }
                //Modify Inlay
                 ModifyTab{id: modifyOptions
                 }

                function open() {
                    width = widthOpen
                    modi.visible = true
                }

                function close() {
                    width = 0
                    modi.visible = false
                    modifyOptions.closefromParent()
                }
            }

        }

    }

}
