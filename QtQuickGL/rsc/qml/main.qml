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
                case Qt.Key_F3:
                    window.setViewMode(2)
                    break
            }
            window.update()
        }
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
                window.scaleView(wheel.angleDelta.y)
                window.update()
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
                Rectangle {
                    id: toggleOptions
                    width: 32
                    height: 32
                    anchors.top: parent.top
                    color: Qt.rgba(0, 0, 0, 0)

                    layer.enabled: true

                    property bool toggle: false
                    property color colorOnHover: Qt.rgba(1,0.25,0,1)
                    property color colorOffHover: Qt.rgba(0,0,0,0.5)

                    Rectangle {
                        id: r1
                        color: parent.colorOffHover
                        width: parent.width - 8
                        height: 4
                        anchors.centerIn: parent
                    }

                    Rectangle {
                        id: r2
                        color: parent.colorOffHover
                        width: parent.width - 8
                        height: 4
                        x: r1.x
                        y: r1.y - 8
                    }

                    Rectangle {
                        id: r3
                        color: parent.colorOffHover
                        width: parent.width - 8
                        height: 4
                        x: r1.x
                        y: r1.y + 8
                    }

                    // ToggleOptions
                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true

                        onEntered: parent.mouseEnterToogleOption()
                        onExited: parent.mouseExitedToogleOption()
                        onClicked: parent.toggleOptions()

                    }

                    function mouseEnterToogleOption() {
                        r1.color = colorOnHover
                        r2.color = colorOnHover
                        r3.color = colorOnHover
                    }

                    function mouseExitedToogleOption() {
                        r1.color = colorOffHover
                        r2.color = colorOffHover
                        r3.color = colorOffHover
                    }

                    function toggleOptions() {
                        if(toggle) {
                            parent.close()
                        } else {
                            parent.open()
                        }
                        toggle = !toggle
                    }

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
                                           font.pointSize: 12; text: "MODIFY" } }
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
