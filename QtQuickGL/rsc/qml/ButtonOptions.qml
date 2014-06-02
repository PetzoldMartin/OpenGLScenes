import QtQuick 2.0

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
