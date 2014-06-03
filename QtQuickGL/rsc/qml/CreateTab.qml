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
                anchors.fill: parent.anchors
                text: "Block"
                onClicked: createTab.createBlock()
            }

            Button {
                anchors.fill: parent.anchors
                text: "Sphere"
                //onClicked: createTab.createBlock()
            }
        }

        Slider {
            id: sizeX
            stepSize: 1
            value: 250
            minimumValue: 1
            maximumValue: 500
            Text {
                id: valueX
                color: "white"
                anchors.left: parent.right
                anchors.leftMargin: 8
            }
            onValueChanged: valueX.text = "size x: " + sizeX.value
        }

        Slider {
            id: sizeY
            stepSize: 1
            value: 250
            minimumValue: 1
            maximumValue: 500
            Text {
                id: valueY
                color: "white"
                anchors.left: parent.right
                anchors.leftMargin: 8
            }
            onValueChanged: valueY.text = "size y: " + sizeY.value
        }

        Slider {
            id: sizeZ
            stepSize: 1
            value: 250
            minimumValue: 1
            maximumValue: 500
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
            stepSize: 1
            value: 250
            minimumValue: 1
            maximumValue: 500
            Text {
                id: posValueX
                color: "white"
                anchors.left: parent.right
                anchors.leftMargin: 8
            }
            onValueChanged: posValueX.text = "pos x: " + posX.value
        }

        Slider {
            id: posY
            stepSize: 1
            value: 250
            minimumValue: 1
            maximumValue: 500
            Text {
                id: posValueY
                color: "white"
                anchors.left: parent.right
                anchors.leftMargin: 8
            }
            onValueChanged: posValueY.text = "pos y: " + posY.value
        }

        Slider {
            id: posZ
            stepSize: 1
            value: 250
            minimumValue: 1
            maximumValue: 500

            property int v: 250

            Text {
                id: posValueZ
                color: "white"
                anchors.left: parent.right
                anchors.leftMargin: 8
            }
            onValueChanged: posValueZ.text = "pos z: " + posZ.value
        }
    }
    function createBlock() {
        window.createBlock(sizeX.value, sizeY.value, sizeZ.value,posX.value,posY.value,posZ.value)
    }
}
