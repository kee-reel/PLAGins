import QtQuick 2.5
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Material 2.12

Item {
    id: root
    width: 1600
    height: 700
    Component {
        id: myButton;
        Button {
            onClicked: links.openLink(Number(text))
        }
    }
    
    Button {
        text: "Click"
        anchors.fill: parent
        background: Rectangle {
            implicitWidth: 100
            implicitHeight: 25
            border.color: "#19A"
            border.width: 30
            color:  "#f0f"
            radius: 90
            gradient: Gradient {
                GradientStop { position: 0.0; color: "white" }
                GradientStop { position: 0.5; color: "blue" }
                GradientStop { position: 1.0; color: "red"}
            }
        }
        onClicked: initButtons()
    }
        
    function initButtons () {
        console.log(String(backEnd.instances))
        for (var i=0; i<3; i++)
        {
            addButton(backEnd.instances[i].uid, 40 + 80 * i)
        }
    }
    
    function addButton (name, y) {
        var button = myButton.createObject(root, {
                                               "text"   : name,
                                               "color"  : "red",
                                               "width"  : 200,
                                               "height" : 80,
                                               "x"      : root.width / 2,
                                               "y"      : y
                                           });
    }
}
