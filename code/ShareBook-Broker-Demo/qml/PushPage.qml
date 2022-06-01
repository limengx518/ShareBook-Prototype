import QtQuick 2.0
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick

Item {
    id:pushPage

    readonly property int rootWidth: pushPage.width
    readonly property int rootHeight: pushPage.height

    Row{
        id:top_banner
        spacing: parent.width*0.08
        anchors.top: parent.top
        anchors.topMargin: parent.height*0.02
        anchors.horizontalCenter: parent.horizontalCenter
        ColumnLayout{
            id:interest
            Text{
//                    font.italic: true
                font.bold: true
                font.pixelSize: 30
                Layout.alignment: Qt.AlignHCenter
                text: qsTr("关注")
            }
            Rectangle{
                id:rect_interest
                width: 30
                height: 5
                radius: 5
                color: "#000000"
                visible: false
                Layout.alignment: Qt.AlignHCenter
            }
            TapHandler{
                onTapped: {
                    rect_interest.visible=true
                    rect_commend.visible=false
                    rect_local.visible=false
                    jsonData=interestData
                    jottingListView.update()
                }
            }
        }
        ColumnLayout{
            id:commend
            Text{
//                    font.italic: true
                font.bold: true
                font.pixelSize: 30
                Layout.alignment: Qt.AlignHCenter
                text: qsTr("推荐")
            }
            Rectangle{
                id:rect_commend
                width: 30
                height: 5
                radius: 5
                color: "#000000"
                visible: true
                Layout.alignment: Qt.AlignHCenter
            }
            TapHandler{
                onTapped: {
                    rect_interest.visible=false
                    rect_commend.visible=true
                    rect_local.visible=false
                    jsonData=commendData
                    jottingListView.update()
                }
            }
        }
        ColumnLayout{
            id:local
            Text{
//                    font.italic: true
                font.bold: true
                font.pixelSize: 30
                Layout.alignment: Qt.AlignHCenter
                text: qsTr("同城")
            }
            Rectangle{
                id:rect_local
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
                    rect_commend.visible=false
                    rect_local.visible=true
                    jsonData=localData
                    jottingListView.update()
                }
            }
        }
    }

    Button{
        id:search_button
        icon.source: "qrc:/images/images/search.png"
        icon.width: rootWidth*0.1
        icon.height: rootWidth*0.1
        width: icon.width
        height: icon.height
        anchors.top: parent.top
        anchors.topMargin: parent.height*0.02
        anchors.right: parent.right
        anchors.rightMargin: parent.width*0.02
        flat: true
        icon.color: "transparent"
        onClicked: {}
    }

}
