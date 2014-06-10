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
                onClicked: createTab.createSphere()
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

        Slider {
            id: colorR
            width: parent.width
            stepSize: 0.015625
            value: 0.5
            minimumValue: 0
            maximumValue: 1
            Text {
                id: valueColorR
                color: "white"
                anchors.left: parent.right
                anchors.leftMargin: 8
                text: "R: " + colorR.value
            }
        }

        Slider {
            id: colorG
            width: parent.width
            stepSize: 0.015625
            value: 0.5
            minimumValue: 0
            maximumValue: 1
            Text {
                id: valueColorG
                color: "white"
                anchors.left: parent.right
                anchors.leftMargin: 8
                text: "G: " + colorG.value
            }
        }

        Slider {
            id: colorB
            width: parent.width
            stepSize: 0.015625
            value: 0.5
            minimumValue: 0
            maximumValue: 1
            Text {
                id: valueColorB
                color: "white"
                anchors.left: parent.right
                anchors.leftMargin: 8
                text: "B: " + colorB.value
            }
        }
    }

    function createBlock() {
        window.createBlock(
                    sizeX.value,sizeY.value,sizeZ.value,
                    posX.value,posY.value,posZ.value,
                    colorR.value,colorG.value,colorB.value)
    }

    function createSphere() {
        window.createSphere(
                    sizeX.value,sizeY.value,sizeZ.value,
                    posX.value,posY.value,posZ.value,
                    colorR.value,colorG.value,colorB.value)
    }
}
