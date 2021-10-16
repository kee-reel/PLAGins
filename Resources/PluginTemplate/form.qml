import QtQuick 2.5
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

Item {
	id: root
	// Reference object of %{REF}
	property var referenceObject: reference.object

	Rectangle {
		anchors.fill: parent
		color: "#2e3440"
	}

	ColumnLayout {
		anchors.fill: parent
		Text {
			id: label
			Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom
			text: referenceObject.testString
			color: "white"
			font.pixelSize: 36 * ratio
		}

		TextField {
			Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
			width: parent.width / 2
			height: 30 * ratio
			placeholderText: "Type in"
			font.pixelSize: 36 * ratio
			onTextChanged: {
				referenceObject.testString = text
			}
		}
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
