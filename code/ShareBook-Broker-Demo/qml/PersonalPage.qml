import QtQuick 2.0
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick

Item {
    id:personalPage
    anchors.fill: parent

    readonly property int rootWidth: personalPage.width
    readonly property int rootHeight: personalPage.height
    readonly property url personalJottingList: "qrc:/qml/qml/PersonalJottingList.qml"
    readonly property url personalRelationList: "qrc:/qml/qml/PersonalRelationList.qml"

    property var jsonData:JSON.parse(netizen.jottings)

    ScrollView{
        anchors.fill: parent
        Rectangle{
            width:parent.width
            Button {
                id: otherSelect_button
                icon.source: "qrc:/images/images/myotherselect.png"
                icon.width: rootWidth*0.1
                icon.height: rootWidth*0.1
                width: icon.width
                height: icon.height
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.margins: rootWidth*0.02
                flat: true
                icon.color: "transparent"
                onClicked: {}
            }

            RowLayout{
                id:row_head_count
                width:rootWidth
                anchors.top: otherSelect_button.bottom
                anchors.left: parent.left
                anchors.topMargin: rootWidth*0.02
                anchors.leftMargin: rootWidth*0.02
                Image{
                    id:headPic_image
                    source: "qrc:/images/images/headpic.png"
                    width: rootWidth*0.3
                    height: rootWidth*0.3
                    fillMode: Image.PreserveAspectFit
                    Layout.alignment: Qt.AlignHCenter
                }
                RowLayout{
                    Layout.alignment: Qt.AlignHCenter
                    spacing: rootWidth*0.06
                    ColumnLayout{
                        id:interest
                        spacing: rootWidth*0.02
                        Text {
                            id: interest_count
                            font.pixelSize:25
                            Layout.alignment: Qt.AlignHCenter
                            text: qsTr(netizen.interestCount)
                        }
                        Text {
                            font.pixelSize:25
                            Layout.alignment: Qt.AlignHCenter
                            text: qsTr("Follower")
                        }
                        TapHandler{
                            onTapped: {
                                loader.setSource(personalRelationList,{"ownName":netizen.nikeName,"dataType":"interest","interestData":JSON.parse(netizen.interest),"fanData":JSON.parse(netizen.fans),"cycleData":JSON.parse(netizen.interest)})
                                loader.line=false
                                loader.buttons=false
                            }
                        }
                    }
                    ColumnLayout{
                        id:fan
                        spacing: rootWidth*0.02
                        Text {
                            id: fan_count
                            font.pixelSize:25
                            Layout.alignment: Qt.AlignHCenter
                            text: qsTr(netizen.fanCount)
                        }
                        Text {
                            font.pixelSize:25
                            Layout.alignment: Qt.AlignHCenter
                            text: qsTr("Fan")
                        }
                        TapHandler{
                            onTapped: {
                                loader.setSource(personalRelationList,{"ownName":netizen.nikeName,"dataType":"fan","interestData":JSON.parse(netizen.interest),"fanData":JSON.parse(netizen.fans),"cycleData":JSON.parse(netizen.interest)})
                                loader.line=false
                                loader.buttons=false
                            }
                        }
                    }
                    ColumnLayout{
                        id:cycle
                        spacing: rootWidth*0.02
                        Text {
                            id: cycle_count
                            font.pixelSize:25
                            Layout.alignment: Qt.AlignHCenter
                            text: qsTr(netizen.interestCount)
                        }
                        Text {
                            font.pixelSize:25
                            Layout.alignment: Qt.AlignHCenter
                            text: qsTr("Cycle")
                        }
                        TapHandler{
                            onTapped: {
                                loader.setSource(personalRelationList,{"ownName":netizen.nikeName,"dataType":"cycle","interestData":JSON.parse(netizen.interest),"fanData":JSON.parse(netizen.fans),"cycleData":JSON.parse(netizen.interest)})
                                loader.line=false
                                loader.buttons=false
                            }
                        }
                    }
                }
            }

            Text {
                id: netizen_name
                anchors.top: row_head_count.bottom
                anchors.left: parent.left
                anchors.topMargin: rootWidth*0.02
                anchors.leftMargin: rootWidth*0.03
                font.pixelSize: 30
                font.bold: true
                text: qsTr(netizen.nikeName)
            }

            Text {
                id: netizen_sign
                anchors.top: netizen_name.bottom
                anchors.left: parent.left
                anchors.topMargin: rootWidth*0.02
                anchors.leftMargin: rootWidth*0.03
                text: qsTr(netizen.sign)
            }

            Rectangle{
                id:seperator_line_1
                width: parent.width
                height: 1
                color: "#000000"
                anchors.top: netizen_sign.bottom
                anchors.topMargin: parent.width*0.05
            }

            Row{
                id:banner
                spacing: parent.width*0.25
                anchors.top: seperator_line_1.bottom
                anchors.topMargin: parent.width*0.01
                anchors.horizontalCenter: parent.horizontalCenter
                ColumnLayout{
                    id:own_jotting
                    Text{
                        font.italic: true
                        font.bold: true
                        font.pixelSize: 30
                        Layout.alignment: Qt.AlignHCenter
                        text: qsTr("Jot")
                    }
                    Rectangle{
                        id:rect_own
                        width: 30
                        height: 5
                        radius: 5
                        color: "#000000"
                        visible: true
                        Layout.alignment: Qt.AlignHCenter
                    }
                    TapHandler{
                        onTapped: {
                            rect_own.visible=true
                            rect_like.visible=false
                            rect_collect.visible=false
                            jsonData=JSON.parse(netizen.jottings)
                        }
                    }
                }
                ColumnLayout{
                    id:like_jotting
                    Text{
                        font.italic: true
                        font.bold: true
                        font.pixelSize: 30
                        Layout.alignment: Qt.AlignHCenter
                        text: qsTr("Like")
                    }
                    Rectangle{
                        id:rect_like
                        width: 30
                        height: 5
                        radius: 5
                        color: "#000000"
                        visible: false
                        Layout.alignment: Qt.AlignHCenter
                    }
                    TapHandler{
                        onTapped: {
                            rect_own.visible=false
                            rect_like.visible=true
                            rect_collect.visible=false
                            jsonData=JSON.parse(netizen.jottings)
                        }
                    }
                }
                ColumnLayout{
                    id:collect_jotting
                    Text{
                        font.italic: true
                        font.bold: true
                        font.pixelSize: 30
                        Layout.alignment: Qt.AlignHCenter
                        text: qsTr("Collect")
                    }
                    Rectangle{
                        id:rect_collect
                        width: 30
                        height: 5
                        radius: 5
                        color: "#000000"
                        visible:false
                        Layout.alignment: Qt.AlignHCenter
                    }
                    TapHandler{
                        onTapped: {
                            rect_own.visible=false
                            rect_like.visible=false
                            rect_collect.visible=true
                            jsonData=JSON.parse(netizen.jottings)
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

            ScrollView{
                width:rootWidth
                height: rootHeight*0.4
                anchors.top: seperator_line_2.bottom
                anchors.left: parent.left
                anchors.topMargin: rootWidth*0.02
                anchors.leftMargin: rootWidth*0.03
                Component{
                    id:jotComponent
                    Rectangle{
                        id: jot
                        width:jotsListView.width*0.465
                        height: jotsListView.height*0.65
                        border.color: "#000000"
                        border.width:1
                        radius: 5
                        Column{
                            spacing: rootHeight*0.01
                            Text {
                                id: pic
                                text: jsonData[index].pic_path
                            }
                            Rectangle{
                                width: jot.width
                                height:1
                                color: "#000000"
                            }
                            Text {
                                width:jot.width
                                id: text_content
                                text: jsonData[index].content
                                wrapMode: Text.WordWrap
                                leftPadding:5
                            }
                        }
                        TapHandler{
                            onTapped: {
                                loader.source=jsonData[index].file
                            }
                        }
                    }
                }

                GridView {
                    id: jotsListView
                    anchors.fill: parent
                    cellWidth: jotsListView.width*0.475
                    cellHeight: jotsListView.height*0.665
                    model: jsonData
                    delegate: jotComponent
                }
            }
        }
    }



}
