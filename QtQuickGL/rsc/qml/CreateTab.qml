import QtQuick 2.0
import QtQuick.Controls 1.1

Rectangle {
    id: createTab
    visible: false

    Column {
        id: properties
        Row {
            anchors.fill: parent.anchors

            Button {
                width: 80
                anchors.fill: parent.anchors
                text: "Block"
                onClicked: createTab.createBlock()
            }

            Button {
                width: 80
                anchors.fill: parent.anchors
                text: "Sphere"
                //onClicked: createTab.createBlock()
            }
        }

        Slider {
            id: sizeX
            width: parent.width
            stepSize: 1
            value: 100
            minimumValue: 1
            maximumValue: 200
            Text {
                id: valueX
                color: "white"
                anchors.left: parent.right
                anchors.leftMargin: 8
                text: "size x: " + sizeX.value
            }
        }

        Slider {
            id: sizeY
            width: parent.width
            stepSize: 1
            value: 100
            minimumValue: 1
            maximumValue: 200
            Text {
                id: valueY
                color: "white"
                anchors.left: parent.right
                anchors.leftMargin: 8
                text: "size y: " + sizeY.value
            }
        }

        Slider {
            id: sizeZ
            width: parent.width
            stepSize: 1
            value: 100
            minimumValue: 1
            maximumValue: 200
            Text {
                id: valueZ
                color: "white"
                anchors.left: parent.right
                anchors.leftMargin: 8
            }
            onValueChanged: valueZ.text = "size z: " + sizeZ.value
        }

        Slider {
            id: posX
            width: parent.width
            stepSize: 1
            value: 0
            minimumValue: -250
            maximumValue: 250
            Text {
                id: posValueX
                color: "white"
                anchors.left: parent.right
                anchors.leftMargin: 8
                text: "pos x: " + posX.value
            }
        }

        Slider {
            id: posY
            width: parent.width
            stepSize: 1
            value: 0.0
            minimumValue: -250
            maximumValue: 250
            Text {
                id: posValueY
                color: "white"
                anchors.left: parent.right
                anchors.leftMargin: 8
                text: "pos y: " + posY.value
            }
        }

        Slider {
            id: posZ
            width: parent.width
            stepSize: 1
            value: 0
            minimumValue: -250
            maximumValue: 250

            Text {
                id: posValueZ
                color: "white"
                anchors.left: parent.right
                anchors.leftMargin: 8
                text: "pos z: " + posZ.value
            }
        }
    }

    function createBlock() {
        window.createBlock(sizeX.value, sizeY.value, sizeZ.value,posX.value,posY.value,posZ.value)
    }
}
