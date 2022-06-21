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

    readonly property url pushPage_loader: "qrc:/qml/qml/PushPage.qml"
    readonly property url cyclePage_loader: "qrc:/qml/qml/CyclePage.qml"
    readonly property url chooseMaterialPage_loader: "qrc:/qml/qml/ChooseMaterialPage.qml"
    readonly property url messagePage_loader: "qrc:/qml/qml/MessagePage.qml"
    readonly property url personalPage_loader: "qrc:/qml/qml/PersonalPage.qml"
    readonly property url jotDetailPage_loader: "qrc:/qml/qml/JotDetailPage.qml"
    readonly property url publishPage_loader: "qrc:/qml/qml/PublishPage.qml"
    readonly property int iconSize_avg:rootWindow.width * 0.2

    property var materialData
    //[
//        {"path":"qrc:/images/images/avatar.png","isSelected":false,"order":""},
//    {"path":"qrc:/images/images/avatar.png","isSelected":false,"order":""},
//    {"path":"qrc:/images/images/avatar.png","isSelected":false,"order":""},
//    {"path":"qrc:/images/images/avatar.png","isSelected":false,"order":""},
//    {"path":"qrc:/images/images/avatar.png","isSelected":false,"order":""},
//    {"path":"qrc:/images/images/avatar.png","isSelected":false,"order":""},
//    {"path":"qrc:/images/images/avatar.png","isSelected":false,"order":""},
//    {"path":"qrc:/images/images/avatar.png","isSelected":false,"order":""},
//    {"path":"qrc:/images/images/avatar.png","isSelected":false,"order":""},
//    {"path":"qrc:/images/images/avatar.png","isSelected":false,"order":""},]

//    RoundImage{
//        width: 100
//        height: 100
//        source: "qrc:/images/images/avatar.png"
//    }

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

    PushPageControl{
        id:pushJottings
    }

    PublishPageControl{
        id:publishControl
        Component.onCompleted: {
            findLocalMaterial()
            materialData=JSON.parse(localMaterial).materials
        }
    }

    Toast{
        id:toast
        rootWidth: rootWindow.width
        rootHeight: rootWindow.height
        anchors.bottom: parent.bottom
        anchors.bottomMargin: rootWindow.height*0.1
    }

    Loader {
        id: loader
        anchors.fill: parent
        asynchronous: true
        source:pushPage_loader
        Component.onCompleted: {
            netizen.initData()
            pushJottings.pushRecommendJottings()
        }
    }

}
