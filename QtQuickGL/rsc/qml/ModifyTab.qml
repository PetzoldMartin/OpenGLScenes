import QtQuick 2.0
import OpenGLUnderQML 1.0
import QtQuick.Controls 1.2

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
    function out(out){
            myConsole.text=out
            myConsole.update()
        }
    function reset(){
        modifySliderScale.value=0;
        modifySliderShiftX.value=0;
        modifySliderShiftY.value=0;
        modifySliderShiftZ.value=0;
        modifySliderX.value=0;
        modifySliderY.value=0;
        modifySliderZ.value=0;
        parent.update();
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
         stepSize: 1
         visible: true
         onValueChanged:{
             window.rotateObject(value,modifySliderY.value,modifySliderZ.value);

         }


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
         stepSize: 1
         visible: true
         onValueChanged:{
             window.rotateObject(modifySliderX.value,modifySliderY.value,modifySliderZ.value);
         }
     }
    Rectangle { id: modifyMonitorZ
                anchors.top: modifySliderY.bottom
                color: Qt.rgba(0,0.0,0,0.5)
                width: parent.width;
                height: parent.componentHeight;
                Text { anchors.right: parent.right
                       anchors.bottom: parent.bottom
                       anchors.bottomMargin: parent.parent.componentTextBottom
                       color: "white"
                       font.pointSize: parent.parent.componentTextSize;
                       text: modifySliderZ.value}
                Text { anchors.centerIn: parent
                       color: "white"
                       font.pointSize: parent.parent.componentTextSize;
                       text: "ZRotation" } }
    Slider {
        id:modifySliderZ
        anchors.top: modifyMonitorZ.bottom
         width: parent.width
         height: parent.componentHeight;
         maximumValue: 180
         minimumValue: -180
         value: 0
         stepSize: 1
         visible: true
         onValueChanged:{
             window.rotateObject(modifySliderX.value,modifySliderY.value,modifySliderZ.value);
         }
     }
    Rectangle { id: modifyMonitorScale
                anchors.top: modifySliderZ.bottom
                color: Qt.rgba(0,0.0,0,0.5)
                width: parent.width;
                height: parent.componentHeight;
                Text { anchors.right: parent.right
                       color: "white"
                       anchors.bottom: parent.bottom
                       anchors.bottomMargin: parent.parent.componentTextBottom
                       font.pointSize: parent.parent.componentTextSize;
                       text: (modifySliderScale.value+100)/100}
                Text { anchors.centerIn: parent
                       color: "white"
                       font.pointSize: parent.parent.componentTextSize;
                       text: "Scale" } }
    Slider {
        id:modifySliderScale
        anchors.top: modifyMonitorScale.bottom
         width: parent.width
         height: parent.componentHeight;

         value: 0
         maximumValue: 100
         minimumValue: -100
         stepSize: 5
         visible: true
         onValueChanged:window.scaleObject((value+100)/100)
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
         maximumValue: 100
         minimumValue: -100
         value: 0
         stepSize: 1
         visible: true
         onValueChanged:{window.shiftObject(modifySliderShiftX.value,modifySliderShiftY.value,modifySliderShiftZ.value);
             }

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
         maximumValue: 100
         minimumValue: -100
         value: 0
         stepSize: 1
         visible: true
         onValueChanged:{window.shiftObject(modifySliderShiftX.value,modifySliderShiftY.value,modifySliderShiftZ.value);
             }

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
         maximumValue: 100
         minimumValue: -100
         value: 0
         stepSize: 1
         visible: true
         onValueChanged:{window.shiftObject(modifySliderShiftX.value,modifySliderShiftY.value,modifySliderShiftZ.value);
             }

     }
    Rectangle { id: modifyMonitorShiftConsole
                    anchors.top: modifySliderShiftZ.bottom
                    color: Qt.rgba(0,0.0,0,0.5)
                    width: parent.width;
                    height: parent.componentHeight;

                    Text {
                           id: myConsole
                           anchors.centerIn: parent
                           color: "white"
                           font.pointSize: parent.parent.componentTextSize;
                           text: "Ausgabe"
                    }
                     }

    Button { text: "Accept"
        id: button
        anchors.top: modifyMonitorShiftConsole.bottom
        //Font.bold: parent.parent.componentTextSize;
        width: parent.width;
        height: parent.componentHeight*2;
        onClicked: {
            window.forceModification();
            window.deselect();

            modifySliderScale.value=0;
            modifySliderShiftX.value=0;
            modifySliderShiftY.value=0;
            modifySliderShiftZ.value=0;
            modifySliderX.value=0;
            modifySliderY.value=0;
            parent.update();
        }
    }
}
