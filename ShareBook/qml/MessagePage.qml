import QtQuick 2.0
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick
import Qt5Compat.GraphicalEffects


Item {
    id:messagePage
    readonly property int rootWidth: messagePage.width
    readonly property int rootHeight: messagePage.height

    Rectangle{
        id:topRec
        width:parent.width
        height:rootWidth*0.1
        Text {
            id: text
            anchors.topMargin: rootWidth*0.1
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            text: qsTr("消息")
            font.pointSize: 18
        }

        Button{
            id:groupChat
            height:parent.height
            anchors.left: text.right
            anchors.leftMargin:  rootWidth*0.28
            background: Rectangle{
                anchors.fill: parent
                color: "white"
            }
            anchors.right: parent.right
            anchors.rightMargin:  rootWidth*0.01
            anchors.verticalCenter: parent.verticalCenter
            RowLayout{
                anchors.verticalCenter: parent.verticalCenter
                Image{
                    id:img
                    source:"qrc:/images/images/groupChat.png"
                    fillMode: Image.PreserveAspectFit
                    sourceSize: Qt.size(15, 15)
                }
                Text{
                    text: qsTr("群聊")
                    font.pointSize: 15
                }
            }
            onClicked: {
                console.log("群聊 被点击了!")
            }
        }

    }


    RowLayout{
        id:midRow
        anchors.top: topRec.bottom
        anchors.topMargin: rootWidth*0.1
        anchors.bottomMargin: rootWidth*0.1
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: rootWidth*0.25
        Button{
            height: parent.height
            background: Rectangle{
                color: "white"
                opacity: 0.7
            }

            ColumnLayout{
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                spacing: rootWidth*0.025
                Image {
                    id: likeImg
                    fillMode: Image.PreserveAspectFit
                    Layout.alignment: Qt.AlignHCenter
                    sourceSize: Qt.size(40, 40)
                    source:"qrc:/images/images/message_like.png"
                }
                Text {
                    id: likeText
                    text: qsTr("赞和收藏")
                    Layout.alignment: Qt.AlignHCenter
                    font.pointSize: 12
                }
            }
            onClicked: {
                console.log("赞和收藏被点击了!")
            }
        }

        Button{
            height: parent.height
            background: Rectangle{
                color: "white"
                opacity: 0.7
            }

            ColumnLayout{
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                spacing: rootWidth*0.025
                Image {
                    id: followImg
                    fillMode: Image.PreserveAspectFit
                    Layout.alignment: Qt.AlignHCenter
                    sourceSize: Qt.size(40, 40)
                    source:"qrc:/images/images/message_follow.png"
                }
                Text {
                    id: followText
                    text: qsTr("新增关注")
                    Layout.alignment: Qt.AlignHCenter
                    font.pointSize: 12
                }
            }
            onClicked: {
                console.log("新增关注被点击了!")
            }
        }

        Button{
            height: parent.height
            background: Rectangle{
                color: "white"
                opacity: 0.7
            }

            ColumnLayout{
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                spacing: rootWidth*0.025
                Image {
                    id: commentImg
                    fillMode: Image.PreserveAspectFit
                    Layout.alignment: Qt.AlignHCenter
                    sourceSize: Qt.size(40, 40)
                    source:"qrc:/images/images/@.png"
                }
                Text {
                    id: commentText
                    text: qsTr("评论和@")
                    Layout.alignment: Qt.AlignHCenter
                    font.pointSize: 12
                }
            }
            onClicked: {
                console.log("评论和@被点击了!")
            }
        }
    }
}
