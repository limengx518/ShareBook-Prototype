import QtQuick 2.0
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick
import UIControl 1.0

Item {
    id:personalRelationList

    readonly property int rootWidth: personalRelationList.width
    readonly property int rootHeight: personalRelationList.height
    readonly property url personalPage: "qrc:/qml/qml/PersonalPage.qml"

    property string ownName:"NULL"
    property string dataType:"interest"
    property var interestData
    property var fanData
    property var cycleData
    property var jsonData: interestData

    Component.onCompleted: {
        if(dataType==="interest"){
            jsonData=interestData
            rect_interest.visible=true
            rect_fan.visible=false
            rect_cycle.visible=false
        }else if(dataType==="fan"){
            jsonData=fanData
            rect_interest.visible=false
            rect_fan.visible=true
            rect_cycle.visible=false
        }else{
            jsonData=cycleData
            rect_interest.visible=false
            rect_fan.visible=false
            rect_cycle.visible=true
        }
    }

    Button{
        id:backButton
        icon.source: "qrc:/images/images/backbutton.png"
        icon.width: rootWidth*0.1
        icon.height: rootWidth*0.1
        width: icon.width
        height: icon.height
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.margins: rootWidth*0.02
        flat: true
        icon.color: "transparent"
        onClicked: {
            loader.source=personalPage
            loader.line=true
            loader.buttons=true
        }
    }

    Text{
        id:netizen_name
        text:ownName
        anchors.top:parent.top
        anchors.topMargin: rootWidth*0.02
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 30
        font.bold: true
    }

    Rectangle{
        id:seperator_line_1
        width: parent.width
        height: 1
        color: "#000000"
        anchors.top: netizen_name.bottom
        anchors.topMargin: parent.width*0.05
    }

    Row{
        id:banner
        spacing: parent.width*0.25
        anchors.top: seperator_line_1.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        ColumnLayout{
            id:interest
            Text{
                font.italic: true
                font.bold: true
                font.pixelSize: 30
                Layout.alignment: Qt.AlignHCenter
                text: qsTr("Follower")
            }
            Rectangle{
                id:rect_interest
                width: 30
                height: 5
                radius: 5
                color: "#000000"
                visible: true
                Layout.alignment: Qt.AlignHCenter
            }
            TapHandler{
                onTapped: {
                    rect_interest.visible=true
                    rect_fan.visible=false
                    rect_cycle.visible=false
                    jsonData=interestData
                    relationListView.update()
                }
            }
        }
        ColumnLayout{
            id:fan
            Text{
                font.italic: true
                font.bold: true
                font.pixelSize: 30
                Layout.alignment: Qt.AlignHCenter
                text: qsTr("Fan")
            }
            Rectangle{
                id:rect_fan
                width: 30
                height: 5
                radius: 5
                color: "#000000"
                visible: false
                Layout.alignment: Qt.AlignHCenter
            }
            TapHandler{
                onTapped: {
                    rect_interest.visible=false
                    rect_fan.visible=true
                    rect_cycle.visible=false
                    jsonData=fanData
                    relationListView.update()
                }
            }
        }
        ColumnLayout{
            id:cycle
            Text{
                font.italic: true
                font.bold: true
                font.pixelSize: 30
                Layout.alignment: Qt.AlignHCenter
                text: qsTr("Cycle")
            }
            Rectangle{
                id:rect_cycle
                width: 30
                height: 5
                radius: 5
                color: "#000000"
                visible:false
                Layout.alignment: Qt.AlignHCenter
            }
            TapHandler{
                onTapped: {
                    rect_interest.visible=false
                    rect_fan.visible=false
                    rect_cycle.visible=true
                    jsonData=cycleData
                    relationListView.update()
                }
            }
        }
    }

    Rectangle{
        id:seperator_line_2
        width: parent.width
        height: 1
        color: "#000000"
        anchors.top: banner.bottom
        anchors.topMargin: parent.width*0.02
    }

//    RoundImage{
//        id:head_image
//        anchors.centerIn: parent
//        width: 40
//        height: 40
//        source: "qrc:/images/images/avatar.png"
////                    anchors.verticalCenter: parent.verticalCenter
//    }

    ScrollView{
        width: rootWidth
        height: rootHeight*0.9
        anchors.top: seperator_line_2.bottom
        anchors.topMargin: rootHeight*0.01
        Component{
            id:relationComponent
            Rectangle{
                id: relation
                width:rootWidth
                height: rootHeight*0.1
                Row{
                    anchors.left: parent.left
                    anchors.leftMargin: rootWidth*0.05
                    spacing: rootWidth*0.1
                    Image{
                        id:head_image
                        width: rootWidth*0.15
                        height: rootWidth*0.15
                        fillMode: Image.PreserveAspectFit
                        source: "qrc:/images/images/avatar.png"
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    Text{
                        width: relation.width
                        text: jsonData[index].nickName
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }
                TapHandler{
                    onTapped: {
                        loader.source="qrc:/qml/qml/JotDetailPage.qml"
                    }
                }
            }
        }


        ListView{
            id: relationListView
            anchors.fill: parent
            model: jsonData
            delegate: relationComponent
        }
    }

}
