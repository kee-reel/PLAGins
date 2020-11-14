import QtQuick 2.5
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

Item {
    id: root

    Rectangle {
        anchors.fill: parent
        color: "#2e3440"
    }

    Text {
        anchors.centerIn: parent
        text: "New plugin"
        color: "white"
        font.pixelSize: 36 * ratio
    }

    Button {
        id: exitButton
        text: "Back"
        font.pixelSize: 18 * ratio
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: 10 * ratio
        width: 60 * ratio
        height: width
        onClicked: uiElement.closeSelf()
        background: Rectangle {
            color: exitButton.pressed ? "#d8dee9" : "#81a1c1"
            radius: 90
        }
    }
}
