import QtQuick 2.5
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.12

Button {
	id: menuItem
	property var uid: -1
	property var name: ""
	icon.source: "qrc:/Res/clipboards.png"
	icon.width: 80 * ratio
	icon.height: 80 * ratio
	icon.color: "#eceff4"
	Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
	onClicked: uiElement.openLink(uid)
	background: Rectangle {
		color: menuItem.pressed ? "#88c0d0" : "#81a1c1"
		radius: 10
	}
	Text {
		id: itemName
		text: name
		font.pixelSize: 18 * ratio
		anchors.topMargin: 10
		anchors.top: menuItem.bottom
		anchors.left: menuItem.left
		anchors.right: menuItem.right
		horizontalAlignment: Text.AlignHCenter
		color: "#eceff4"
	}
}
