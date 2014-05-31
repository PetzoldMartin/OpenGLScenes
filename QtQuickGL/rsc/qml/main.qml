import QtQuick 2.0
import OpenGLUnderQML 1.0
import QtQuick.Controls 1.1

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
            window.mouseX=mouse.x
        }

        onMouseYChanged:  {
            console.log("DeltaY Mouse: "+ (mouse.y-window.mouseY))
            window.rotateView(0,mouse.y-window.mouseY)
            window.mouseY=mouse.y
        }

        onPressed: {
            console.log("mousePressed");
            if (mouse.button == Qt.LeftButton){
                console.log("Pick Object")
            window.selectedObjectId = window.pickObjectAt(mouse.x,mouse.y)
            window.mouseX=mouse.x
            window.mouseY=mouse.y}
            if (mouse.button == Qt.RightButton){
                console.log("Object Menu")
                toggleOptions.toggleOptions()



        }
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
                Rectangle{
                    id: modifyOptions
                    anchors.bottom: parent.bottom
                    width: parent.width
                    height: parent.height-32
                    anchors.left: parent.left
                    color: Qt.rgba(0,0,0,0.5)
                    visible: false
                    property bool toggle: false
                    property int componentHeight:30//parent.height/14
                    property int componentTextSize:16//parent.height/28
                    property int componentTextBottom: componentHeight/2-componentTextSize+componentTextSize/6

                    function toggleOptions() {
                        if(toggle) {
                            close()
                        } else {
                            open()
                        }
                        toggle = !toggle
                    }
                    function open() {
                        width = parent.width
                        modifyOptions.visible = true
                    }

                    function close() {
                        width = 0
                        modifyOptions.visible = false
                    }
                    function closefromParent() {
                        toggle=false
                        width = 0
                        modifyOptions.visible = false
                    }
                    Rectangle { id: modifyMonitorX
                                color: Qt.rgba(0,0.0,0,0.5)
                                width: parent.width;
                                height: parent.componentHeight;
                                Text {
                                       anchors.right: parent.right
                                       color: "white"
                                       anchors.bottom: parent.bottom
                                       anchors.bottomMargin: parent.parent.componentTextBottom
                                       font.pointSize: parent.parent.componentTextSize;
                                       text: modifySliderX.value}
                                Text { anchors.centerIn: parent
                                       color: "white"
                                       font.pointSize: parent.parent.componentTextSize;
                                       text: "XRotation" } }

                    Slider {
                        id:modifySliderX
                         width: parent.width
                         height: parent.componentHeight;
                         anchors.top: modifyMonitorX.bottom
                         maximumValue: 180
                         minimumValue: -180
                         value: 0
                         stepSize: 10
                         visible: true
                         onValueChanged:window.rotateObject(window.selectedObjectId,value,modifySliderY.value)
                     }
                    Rectangle { id: modifyMonitorY
                                anchors.top: modifySliderX.bottom
                                color: Qt.rgba(0,0.0,0,0.5)
                                width: parent.width;
                                height: parent.componentHeight;
                                Text { anchors.right: parent.right
                                       anchors.bottom: parent.bottom
                                       anchors.bottomMargin: parent.parent.componentTextBottom
                                       color: "white"
                                       font.pointSize: parent.parent.componentTextSize;
                                       text: modifySliderY.value}
                                Text { anchors.centerIn: parent
                                       color: "white"
                                       font.pointSize: parent.parent.componentTextSize;
                                       text: "YRotation" } }
                    Slider {
                        id:modifySliderY
                        anchors.top: modifyMonitorY.bottom
                         width: parent.width
                         height: parent.componentHeight;
                         maximumValue: 180
                         minimumValue: -180
                         value: 0
                         stepSize: 10
                         visible: true
                         onValueChanged:window.rotateObject(window.selectedObjectId,modifySliderX.value,value)
                     }
                    Rectangle { id: modifyMonitorScale
                                anchors.top: modifySliderY.bottom
                                color: Qt.rgba(0,0.0,0,0.5)
                                width: parent.width;
                                height: parent.componentHeight;
                                Text { anchors.right: parent.right
                                       color: "white"
                                       anchors.bottom: parent.bottom
                                       anchors.bottomMargin: parent.parent.componentTextBottom
                                       font.pointSize: parent.parent.componentTextSize;
                                       text: modifySliderScale.value}
                                Text { anchors.centerIn: parent
                                       color: "white"
                                       font.pointSize: parent.parent.componentTextSize;
                                       text: "Scale" } }
                    Slider {
                        id:modifySliderScale
                        anchors.top: modifyMonitorScale.bottom
                         width: parent.width
                         height: parent.componentHeight;
                         maximumValue: 10
                         minimumValue: -10
                         value: 0
                         stepSize: 1
                         visible: true
                         onValueChanged:window.scaleObject(window.selectedObjectId,value)
                     }
                    Rectangle { id: modifyMonitorShiftX
                                anchors.top: modifySliderScale.bottom
                                color: Qt.rgba(0,0.0,0,0.5)
                                width: parent.width;
                                height: parent.componentHeight;
                                Text { anchors.right: parent.right
                                       color: "white"
                                       anchors.bottom: parent.bottom
                                       anchors.bottomMargin: parent.parent.componentTextBottom
                                       font.pointSize: parent.parent.componentTextSize;
                                       text: modifySliderShiftX.value}
                                Text { anchors.centerIn: parent
                                       color: "white"
                                       font.pointSize: parent.parent.componentTextSize;
                                       text: "ShiftX" } }
                    Slider {
                        id:modifySliderShiftX
                        anchors.top: modifyMonitorShiftX.bottom
                         width: parent.width
                         height: parent.componentHeight;
                         maximumValue: 10
                         minimumValue: -10
                         value: 0
                         stepSize: 0.5
                         visible: true
                         onValueChanged:window.shiftObject(window.selectedObjectId,modifySliderShiftX.value,modifySliderShiftY.value,modifySliderShiftZ.value)
                     }
                    Rectangle { id: modifyMonitorShiftY
                                anchors.top: modifySliderShiftX.bottom
                                color: Qt.rgba(0,0.0,0,0.5)
                                width: parent.width;
                                height: parent.componentHeight;
                                Text { anchors.right: parent.right
                                       color: "white"
                                       anchors.bottom: parent.bottom
                                       anchors.bottomMargin: parent.parent.componentTextBottom
                                       font.pointSize: parent.parent.componentTextSize;
                                       text: modifySliderShiftY.value}
                                Text { anchors.centerIn: parent
                                       color: "white"
                                       font.pointSize: parent.parent.componentTextSize;
                                       text: "ShiftY" } }
                    Slider {
                        id:modifySliderShiftY
                        anchors.top: modifyMonitorShiftY.bottom
                         width: parent.width
                         height: parent.componentHeight;
                         maximumValue: 10
                         minimumValue: -10
                         value: 0
                         stepSize: 0.5
                         visible: true
                         onValueChanged:window.shiftObject(window.selectedObjectId,modifySliderShiftX.value,modifySliderShiftY.value,modifySliderShiftZ.value)

                     }
                    Rectangle { id: modifyMonitorShiftZ
                                anchors.top: modifySliderShiftY.bottom
                                color: Qt.rgba(0,0.0,0,0.5)
                                width: parent.width;
                                height: parent.componentHeight;
                                Text { anchors.right: parent.right
                                       color: "white"
                                       anchors.bottom: parent.bottom
                                       anchors.bottomMargin: parent.parent.componentTextBottom
                                       font.pointSize: parent.parent.componentTextSize;
                                       text: modifySliderShiftZ.value}
                                Text { anchors.centerIn: parent
                                       color: "white"
                                       font.pointSize: parent.parent.componentTextSize;
                                       text: "ShiftZ" } }
                    Slider {
                        id:modifySliderShiftZ
                        anchors.top: modifyMonitorShiftZ.bottom
                         width: parent.width
                         height: parent.componentHeight;
                         maximumValue: 10
                         minimumValue: -10
                         value: 0
                         stepSize: 0.5
                         visible: true
                         onValueChanged:window.shiftObject(window.selectedObjectId,modifySliderShiftX.value,modifySliderShiftY.value,modifySliderShiftZ.value)

                     }


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
