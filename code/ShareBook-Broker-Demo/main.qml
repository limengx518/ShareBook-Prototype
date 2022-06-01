import QtQuick
import QtQuick.Controls
import UIControl 1.0

Window {
    id:rootWindow
    width: 543
    height: 1000
    visible: true
    title: qsTr("ShareBook")
    color: "#ffffff"

    readonly property url pushPage: "qrc:/qml/qml/PushPage.qml"
    readonly property url cyclePage: "qrc:/qml/qml/CyclePage.qml"
    readonly property url publishPage: "qrc:/qml/qml/PublishPage.qml"
    readonly property url messagePage: "qrc:/qml/qml/MessagePage.qml"
    readonly property url personalPage: "qrc:/qml/qml/PersonalPage.qml"
    readonly property int iconSize_avg:rootWindow.width * 0.2
    readonly property url jotDetailPage: "qrc:/qml/qml/JotDetailPage.qml"

    QtObject {
        id: settings
        // Toggle default visibility of these views
        property bool showSettingsView: true
        property bool showLoggingView: false
        // Fonts in pointSizes
        // These are used mostly on examples in 3D side
        property real fontSizeLarge: 16
        // These are used mostly on settings
        property real fontSizeSmall: 10
    }

    PersonalUIControl{
        id:netizen
    }

    Loader {
        id: loader
        anchors.fill: parent
        asynchronous: true
        property alias line: seperator_line.visible
        property alias buttons:bottom_button.visible
        source:pushPage
        Component.onCompleted: {
            netizen.initData()
        }
    }


    Rectangle{
        id:seperator_line
        width: parent.width
        height: 1
        color: "#000000"
//        opacity: loader.source !== jotDetailPage
        visible: loader.source !== jotDetailPage
        anchors.bottom: bottom_button.top
    }

    Row{
        id:bottom_button
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
//        opacity: loader.source !== jotDetailPage
        visible: loader.source !== jotDetailPage

        Button {
            id: homebutton
            icon.source: "qrc:/images/images/home.png"
            icon.width: iconSize_avg
            icon.height: iconSize_avg
            width: icon.width
            height: icon.height
            flat: true
            onClicked: {
                loader.source = pushPage;
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
                loader.source = cyclePage;
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
                loader.source = publishPage;
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
                loader.source = messagePage;
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
//                loader.setSource(personalPage,{"netizenName":netizen.nikeName,"netizenSign":netizen.sign});
                loader.source=personalPage
            }
        }
    }

}
