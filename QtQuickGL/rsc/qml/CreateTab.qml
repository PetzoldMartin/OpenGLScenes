import QtQuick 2.0
import QtQuick.Controls 1.1

Rectangle {
    id: createTab
    visible: false

    Button {
        text: Block
        onClicked: window.genRandomBlock()
    }

}
