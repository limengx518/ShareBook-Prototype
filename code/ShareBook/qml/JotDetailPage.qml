import QtQuick 2.0
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick

Item {
    id:jotDetailPage

    readonly property int rootWidth: jotDetailPage.width
    readonly property int rootHeight: jotDetailPage.height

    property string type: "detail"

    property var jottingInfo

    property var temp: jottingInfo.commend

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
            if(type=="preview"){
                loader.setSource(publishPage_loader,{"materialData":jottingInfo.picPath,"content_property":jottingInfo.content})
            }else if(type=="push"){
                loader.source=pushPage_loader
            }else if(type=="self"){
                loader.source=personalPage_loader
            }
        }
    }

    Row{
        id:netizen_info
        anchors.left: backButton.right
        anchors.leftMargin: rootWidth*0.05
        spacing: rootWidth*0.05
        Image{
            id:head_pic
            fillMode: Image.PreserveAspectFit
            source: jottingInfo.avatar
            width: rootWidth*0.15
            height: rootWidth*0.15
            anchors.verticalCenter: parent.verticalCenter
        }
        Text{
            id:netizen_name
            text: qsTr(jottingInfo.netizenName)
            anchors.verticalCenter: parent.verticalCenter
        }
        Row{
            id:funtions
            spacing: rootWidth*0.05
            leftPadding:rootWidth*0.2
            anchors.verticalCenter: parent.verticalCenter
            Rectangle{
                id: concern_button
                width: rootWidth*0.15
                height: concern_button_text.height
                anchors.verticalCenter: parent.verticalCenter
                border.width: 1
                border.color: "black"
                radius: 5
                Text{
                    id:concern_button_text
                    text: qsTr("关注")
                    color: "black"
                    anchors.centerIn: parent
                }
            }
            Button{
                id: share_jotting_button
                icon.source: "qrc:/images/images/transit.png"
                icon.width: rootWidth*0.1
                icon.height: rootWidth*0.1
                width: icon.width
                height: icon.height
                flat: true
                icon.color: "transparent"
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }

    Rectangle{
        id:seperator_line_1
        width: parent.width
        height: 1
        color: "grey"
        anchors.top: netizen_info.bottom
        anchors.topMargin: parent.height*0.01
    }

    ScrollView{
        id:jotting_content
        anchors.top: seperator_line_1.bottom
        anchors.bottom: mark_banner.top
        width: rootWidth
        contentWidth:rootWidth
        contentHeight:image_area.height+indicator.height+content.height+time.height+commend_count.height+rootHeight*0.2+commendListView.contentHeight
        SwipeView{
            id:image_area
            width: rootWidth
            height: rootHeight*0.4
            currentIndex: indicator.currentIndex
            Repeater{
                model:jottingInfo.picPath
                Image{
                    width: rootWidth
                    height: parent.height
                    fillMode: Image.PreserveAspectFit
                    source:jottingInfo.picPath[index].path
                }
            }
        }

        PageIndicator {
            id: indicator
            anchors.top: image_area.bottom
            anchors.topMargin: rootHeight*0.01
            count: image_area.count
            currentIndex: image_area.currentIndex
            interactive: true //可以点击
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Text{
            id:content
            anchors.top: indicator.bottom
            anchors.left: parent.left
            anchors.margins: rootWidth*0.02
            text:qsTr(jottingInfo.content)
            font.pixelSize: 22
            wrapMode: Text.WordWrap
            clip:true
            elide: Text.ElideRight
        }

        Text{
            id:time
            anchors.top: content.bottom
            anchors.left: parent.left
            anchors.margins: rootWidth*0.02
            text: qsTr(jottingInfo.time)
            font.pixelSize: 18
            color: "grey"
        }

        Rectangle{
            id:seperator_line_2
            width: parent.width
            height: 1
            color: "grey"
            anchors.top: time.bottom
            anchors.topMargin: parent.height*0.01
        }

        Text{
            id:commend_count
            anchors.top: seperator_line_2.bottom
            anchors.left: parent.left
            anchors.margins: rootWidth*0.02
            text: qsTr("共"+jottingInfo.commentCount+"条评论")
            font.pixelSize: 18
            color: "grey"
        }

        Component{
            id:commend
            Rectangle{
                width:rootWidth
                Image{
                    id:commend_pic
                    fillMode: Image.PreserveAspectFit
                    source: jottingInfo.commend[index].pic
                    width: rootWidth*0.15
                    height: rootWidth*0.15
                }
                Rectangle{
                    anchors.left:commend_pic.right
                    anchors.margins: rootWidth*0.05
                    Text {
                        id: commend_name
                        font.bold: true
                        font.pixelSize: 20
                        color: "grey"
                        text: qsTr(jottingInfo.commend[index].netizenName)
                    }
                    Text {
                        id: commend_content
                        anchors.top: commend_name.bottom
                        anchors.topMargin: rootWidth*0.01
                        font.pixelSize: 20
                        text: qsTr(jottingInfo.commend[index].content)
                    }
                    Text {
                        id: commend_time
                        anchors.top: commend_content.bottom
                        anchors.topMargin: rootWidth*0.01
                        color: "grey"
                        font.pixelSize: 15
                        text: qsTr(jottingInfo.commend[index].time)
                    }
                }
            }
        }

        ListView{
            id:commendListView
            width: rootWidth
            height: rootHeight
            anchors.top: commend_count.bottom
            anchors.left: parent.left
            anchors.margins: rootWidth*0.02
            model:jottingInfo.commend
            delegate:commend
            spacing:rootHeight*0.1
            clip: true
        }
    }

    Row{
        id:mark_banner
        width: rootWidth
        height: rootHeight*0.05
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.margins: rootWidth*0.02
        topPadding:rootWidth*0.01
        spacing: rootWidth*0.04
        Rectangle{
            width: rootWidth*0.35
            height: rootHeight*0.05
            radius: 45
            color:"grey"
            Row{
                anchors.centerIn: parent
                IconImage{
                    width:rootWidth*0.1
                    height:width
                    source: "qrc:/images/images/comment.png"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Text{
                    text: qsTr("发布评论")
                    font.pixelSize: 22
                    anchors.verticalCenter: parent.verticalCenter
                }
                TapHandler{
                    onTapped: {
                        if(type!=="preview"){
                            jotDetailPage.showComment(edit_comment)
                        }
                    }
                }
            }
        }
        Row{
            id:like_banner
            Button{
                id: like_button_banner
                icon.source: "qrc:/images/images/like.png"
                icon.width: rootWidth*0.1
                icon.height: rootWidth*0.1
                width: icon.width
                height: icon.height
                flat: true
                anchors.verticalCenter: parent.verticalCenter
            }
            Text{
                id:like_count_banner
                width: rootWidth*0.05
                text: qsTr(jottingInfo.likeCount)
                anchors.verticalCenter: parent.verticalCenter
            }
        }
        Row{
            id:collect_banner
            Button{
                id: collect_button_banner
                icon.source: "qrc:/images/images/collect.png"
                icon.width: rootWidth*0.1
                icon.height: rootWidth*0.1
                width: icon.width
                height: icon.height
                flat: true
                anchors.verticalCenter: parent.verticalCenter
            }
            Text{
                id:collect_count_banner
                width: rootWidth*0.05
                text: qsTr(jottingInfo.collectCount)
                anchors.verticalCenter: parent.verticalCenter
            }
        }
        Row{
            id:commend_banner
            Button{
                id: commend_button_banner
                icon.source: "qrc:/images/images/commend.png"
                icon.width: rootWidth*0.1
                icon.height: rootWidth*0.1
                width: icon.width
                height: icon.height
                flat: true
                anchors.verticalCenter: parent.verticalCenter
            }
            Text{
                id:commend_count_banner
                width: rootWidth*0.05
                text: qsTr(jottingInfo.commentCount)
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }

    //comment popup
    Popup{
        id:comment_pop
        modal: true
        focus: true
        padding: 0
        closePolicy: Popup.CloseOnEscape|Popup.CloseOnPressOutside
        property var edit: null
        background: Rectangle{
            color: Qt.rgba(0,0,0,0)
        }
        Loader{
            id:loader_edit
            onLoaded: {
                comment_pop.x=(rootWidth - loader_edit.width) * 0.5
                comment_pop.y=rootHeight - loader_edit.height
            }
        }
        onOpened: {
            loader_edit.sourceComponent = comment_pop.edit
        }
        onClosed: {
            loader_edit.sourceComponent = null
            comment_pop.edit = null
        }
    }

    function showComment(edit){
        comment_pop.edit=edit
        comment_pop.open()
    }

    Component{
        id:edit_comment
        Rectangle{
            width: rootWidth
            height: comment_rect.height+rootHeight*0.05
            color: "#DCDCDC"
            Row{
                anchors.centerIn: parent
                spacing: rootWidth*0.02
                Rectangle{
                    id:comment_rect
                    width: rootWidth*0.8
                    height: rootHeight*0.05
                    color: "white"
                    radius: 45
                    anchors.verticalCenter: parent.verticalCenter
                    ScrollView{
                        anchors.fill: parent
                        TextArea{
                            id:comment_edit
                            wrapMode: TextEdit.WrapAnywhere
                            topPadding:rootWidth*0.02
                            leftPadding:rootWidth*0.02
                            rightPadding:rootWidth*0.02
//                            onTextChanged: {
//                                comment_rect.height=comment_edit.height+rootWidth*0.04
//                            }
                        }
                    }
                }
                Button{
                    id:sent_comment
                    text: qsTr("发送")
                    font.pixelSize: 25
                    flat: true
                    anchors.verticalCenter: parent.verticalCenter
                    onClicked: {
                        if(comment_edit.text===""){
                            toast.anchors.bottomMargin=rootWindow.height*0.5
                            toast.show("请填写内容再发送!")
                            toast.anchors.bottomMargin=rootWindow.height*0.1
                        }else{
                            jottingInfo.commend.push({"netizenName":netizen.nikeName,"pic":"qrc:/images/images/avatar.png","content":comment_edit.text,"time":"2022-06-01 14:12"})
                            commendListView.model=jottingInfo.commend
                            commendListView.update()
                            comment_pop.close()
                        }
                    }
                }
            }

        }
    }
}
