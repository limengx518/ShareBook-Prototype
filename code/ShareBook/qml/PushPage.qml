import QtQuick 2.0
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick

Item {
    id:pushPage

    readonly property int rootWidth: pushPage.width
    readonly property int rootHeight: pushPage.height
    readonly property url personalPage: "qrc:/qml/qml/JotDetailPage.qml"

    property bool isGetConcerned: false
    property bool isGetLocal: false

    property var recommend_jottings:JSON.parse(pushJottings.recommendJottings).jottings
    property var concerned_jottings
    property var local_jottings

    property var jottings: recommend_jottings

    property var jotting_detail

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
                    if(!isGetConcerned){
                        pushJottings.pushConcernedJottings()
                        concerned_jottings=JSON.parse(pushJottings.concernedJottings).jottings
                        isGetConcerned=true
                    }
                    rect_interest.visible=true
                    rect_commend.visible=false
                    rect_local.visible=false
                    jottings=concerned_jottings
                    jottingsListView.update()
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
                    jottings=recommend_jottings
                    jottingsListView.update()
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
                    if(!isGetLocal){
                        pushJottings.pushLocalJottings()
                        local_jottings=JSON.parse(pushJottings.localJottings).jottings
                        isGetLocal=true
                    }
                    rect_interest.visible=false
                    rect_commend.visible=false
                    rect_local.visible=true
                    jottings=local_jottings
                    jottingsListView.update()
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

    Rectangle{
        id:seperator_line_1
        width: parent.width
        height: 1
        color: "#000000"
        anchors.top: search_button.bottom
        anchors.topMargin: parent.height*0.01
    }

    ScrollView{
        width: rootWidth
        height: rootHeight*0.8
        anchors.top: seperator_line_1.bottom
        anchors.topMargin: rootHeight*0.01
        Component{
            id:jottingComponent
            Rectangle{
                id: jotting
                width:rootWidth
//                height: head_banner.height+image_area.height+content_button.height+content.height+check_detail_button.height
                height:rootHeight*0.5
                radius: 10
                border.color: "#000000"
                border.width:1
                Row{
                    id:head_banner
                    anchors.left: parent.left
                    anchors.leftMargin: rootWidth*0.05
                    spacing: rootWidth*0.1
                    Image{
                        id:head_pic
                        width: rootWidth*0.1
                        height: width
                        source: jottings[index].avatar
                        fillMode: Image.PreserveAspectFit
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    Text{
                        width: rootWidth*0.7
                        text: qsTr(jottings[index].nickName)
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }
                Button{
                    id:other_choice
                    icon.source: "qrc:/images/images/otherchoice.png"
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

                Rectangle{
                    id:seperator_line_2
                    width: parent.width
                    height: 1
                    color: "grey"
                    anchors.top: head_banner.bottom
                    anchors.topMargin: parent.height*0.01
                }

                SwipeView{
                    id:image_area
                    width: rootWidth
                    height: rootHeight*0.3
                    anchors.top: seperator_line_2.bottom
                    currentIndex: indicator.currentIndex
                    Repeater{
                        model:jottings[index].picPath
                        Image{
                            width: rootWidth
                            height: parent.height
                            fillMode: Image.PreserveAspectFit
                            source:jottings[index].picPath[index].path
                        }
                    }
                }

                RowLayout{
                    id:content_button
                    anchors.top: image_area.bottom
                    anchors.left: parent.left
                    anchors.leftMargin: rootWidth*0.02
                    Row{
                        spacing: rootWidth*0.01
                        Layout.alignment: Qt.AlignVCenter
                        Button{
                            id:like
                            icon.source: "qrc:/images/images/like.png"
                            icon.width: rootWidth*0.1
                            icon.height: rootWidth*0.1
                            width: icon.width
                            height: icon.height
                            flat: true
                            icon.color: "transparent"
                            onClicked: {}
                        }
                        Button{
                            id:collect
                            icon.source: "qrc:/images/images/collect.png"
                            icon.width: rootWidth*0.1
                            icon.height: rootWidth*0.1
                            width: icon.width
                            height: icon.height
                            flat: true
                            icon.color: "transparent"
                            onClicked: {}
                        }
                    }
                    PageIndicator {
                        id: indicator
                        count: image_area.count
                        currentIndex: image_area.currentIndex
                        interactive: true //可以点击
                        Layout.alignment: Qt.AlignVCenter
                        leftPadding: rootWidth*0.25
                    }
                }
                Button{
                    id:transit
                    icon.source: "qrc:/images/images/transit.png"
                    icon.width: rootWidth*0.1
                    icon.height: rootWidth*0.1
                    width: icon.width
                    height: icon.height
                    anchors.top:image_area.bottom
                    anchors.right: parent.right
                    anchors.rightMargin: parent.width*0.02
                    flat: true
                    icon.color: "transparent"
                    Layout.alignment: Qt.AlignVCenter
                    onClicked: {}
                }

                Row{
                    id:content_show
                    width: parent.width
                    anchors.top:content_button.bottom
                    rightPadding:rootWidth*0.05
                    leftPadding:rootWidth*0.05
                    bottomPadding:rootWidth*0.01
                    topPadding:rootWidth*0.01
                    Text{
                        id:content_name
                        text: qsTr(jottings[index].nickName+": ")
                        font.pixelSize: 22
                        font.bold: true
                    }
                    Text{
                        id:content_text
                        text: qsTr(jottings[index].content)
                        width: parent.width
                        font.pixelSize: 22
                        wrapMode: Text.WordWrap
                        clip:true
                        elide: Text.ElideRight
                    }
                }

                Text{
                    id:check_detail_button
                    anchors.top:content_show.bottom
                    text: qsTr("查看全文")
                    font.italic: true
                    color:"blue"
                    rightPadding:rootWidth*0.05
                    bottomPadding:rootWidth*0.05
                    font.pixelSize: 18
                    anchors.right: parent.right
                    TapHandler{
                        onTapped: {}
                    }
                }
                TapHandler{
                    onTapped: {
                        pushJottings.receiveOneJotting("1")
                        jotting_detail=JSON.parse(pushJottings.jotting)
                        loader.setSource(jotDetailPage_loader,{"type":"push","jottingInfo":jotting_detail})
                    }
                }
            }
        }

        ListView{
            id: jottingsListView
            anchors.fill: parent
            model: jottings
            delegate: jottingComponent
            spacing:rootHeight*0.01
        }
    }

    //底部导航栏
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
                loader.source = pushPage_loader
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
                loader.source = cyclePage_loader
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
                loader.source = messagePage_loader
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
