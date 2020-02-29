import QtQuick 2.5
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3

Item {
	id: root
	property var ratio: 1
	
	Rectangle {
		anchors.fill: parent
		color: "#3b4252"
	}
	
	Button {
		id: exitButton
		width: 80 * ratio
		height: 80 * ratio
		topPadding: 2
		icon.source: "qrc:/Res/back.png"
		icon.color: "#eceff4"
		icon.width: 30 * ratio
		icon.height: 30 * ratio
		onClicked: uiElement.closeSelf()
		anchors.left: parent.left
		anchors.top: parent.top
		anchors.leftMargin: 10
		anchors.topMargin: 20
		anchors.bottomMargin: 55
		background: Rectangle {
			color: exitButton.pressed ? "#88c0d0" : "#3b4252"
			radius: 90
		}
	}
	
	GridLayout {
		id: grid
		anchors.top: exitButton.bottom
		anchors.left: parent.left
		anchors.right: parent.right
		anchors.bottom: parent.bottom
		anchors.margins: 40 * ratio
		columnSpacing: anchors.margins * 2
		columns: (children.length !== 0) ? (parent.width / (children[0].width + 2 * anchors.margins)) : 1
	}
	
	function recreateMenuItems () {
		grid.children = []
		for (var i = 0; i < elements.count; i++)
		{
			addButton(elements.instances[i])
		}
	}
	
	function addButton (element) {
		var component = Qt.createComponent("qrc:/MenuItem.qml")
		var button = component.createObject(grid, {
												"uid": element.uid,
												"name": element.name
											});
	}
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:960;width:540}
}
##^##*/
