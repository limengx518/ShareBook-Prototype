import QtQuick 2.0
import QtQuick.Controls

Item {
    Text {
        id: text
        text: qsTr("message")
    }
    Rectangle{
        id:seperator_line
        width: parent.width
        height: 1
        color: "#000000"
        anchors.bottom: bottom_button.top
    }

    Row{
        id:bottom_button
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        Button {
            id: homebutton
            icon.source: "qrc:/images/images/home.png"
            icon.width: iconSize_avg
            icon.height: iconSize_avg
            width: icon.width
            height: icon.height
            flat: true
            onClicked: {
                loader.source = pushPage_loader;
            }
        }
        Button {
            id: cyclebutton
            icon.source: "qrc:/images/images/cycle.png"
            icon.width: iconSize_avg
            icon.height: iconSize_avg
            width: icon.width
            height: icon.height
            flat: true
            onClicked: {
                loader.source = cyclePage_loader;
            }
        }
        Button {
            id: publishbutton
            icon.source: "qrc:/images/images/publish.png"
            icon.width: iconSize_avg
            icon.height: iconSize_avg
            width: icon.width
            height: icon.height
            flat: true
            onClicked: {
                loader.source = chooseMaterialPage_loader
            }
        }
        Button {
            id: messagebutton
            icon.source: "qrc:/images/images/message.png"
            icon.width: iconSize_avg
            icon.height: iconSize_avg
            width: icon.width
            height: icon.height
            flat: true
            onClicked: {
                loader.source = messagePage_loader;
            }
        }
        Button {
            id: personalbutton
            icon.source: "qrc:/images/images/personal.png"
            icon.width: iconSize_avg
            icon.height: iconSize_avg
            width: icon.width
            height: icon.height
            flat: true
            onClicked: {
                loader.source=personalPage_loader
            }
        }
    }
}
