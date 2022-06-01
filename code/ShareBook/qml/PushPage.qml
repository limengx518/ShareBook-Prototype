import QtQuick 2.0
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick

Item {
    id:pushPage

    readonly property int rootWidth: pushPage.width
    readonly property int rootHeight: pushPage.height

    Row{
        spacing: parent.width*0.0001
        anchors.top: parent.top
        anchors.topMargin: parent.height*0.02
        anchors.right: parent.right
        anchors.rightMargin: parent.width*0.02

        Row{
            id:top_banner
            spacing: parent.width*0.2
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
        Button{
            id:search_button
            icon.source: "qrc:/images/images/myotherselect.png"
            icon.width: rootWidth*0.1
            icon.height: rootWidth*0.1
            width: icon.width
            height: icon.height
            flat: true
            icon.color: "transparent"
            onClicked: {}
        }
    }
}
