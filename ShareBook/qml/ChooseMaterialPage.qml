import QtQuick 2.0
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id:chooseMaterialPage

    readonly property int rootWidth: chooseMaterialPage.width
    readonly property int rootHeight: chooseMaterialPage.height
//    property var selectMaterialItem: []
    property var selectMaterialData: []
    property int materialCount: 0

    function resortMaterial(cancel_text){
        selectMaterialData.splice(parseInt(cancel_text)-1,1)
        var count=0
        for(var i=0;i<materialData.length;i++){
            if(count===materialCount) break;
            if(materialData[i].order!==""){
                ++count
                if(parseInt(materialData[i].order)>parseInt(cancel_text)){
                    materialData[i].order=""+(parseInt(materialData[i].order)-1)
                }
            }
        }
        materialsListView.model=materialData
        materialsListView.update()
    }

    function changePrimeStyle(){
        if(materialCount>0){
            material_count_border.color="white"
            material_count_border.border.color="black"
            material_count_border.border.width=1
        }else{
            material_count_border.color="grey"
            material_count_border.border.color="#ffffff"
            material_count_border.border.width=0
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
        onClicked: {
            loader.source=pushPage_loader
        }
    }

    Text{
        id:netizen_name
        text:qsTr("选择素材")
        anchors.top:parent.top
        anchors.topMargin: rootWidth*0.02
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 30
        font.bold: true
    }

    Rectangle{
        id:material_count_border
        radius: 45
//        color: "grey"
        width: rootWidth*0.15
        height: rootHeight*0.04
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: rootWidth*0.03
        Text {
            id:material_count
            anchors.centerIn: parent
            text: qsTr("Finish")
        }
        TapHandler{
            onTapped: {
                if(materialCount>0){
                    loader.setSource(publishPage_loader,{"materialPath":selectMaterialData})
                }else{
                    toast.show("Please choose materials")
                }
            }
        }
        Component.onCompleted: {
            changePrimeStyle()
        }
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
            id:all
            Text{
                font.italic: true
                font.bold: true
                font.pixelSize: 30
                Layout.alignment: Qt.AlignHCenter
                text: qsTr("全部")
            }
            Rectangle{
                id:rect_all
                width: 30
                height: 5
                radius: 5
                color: "#000000"
                visible: true
                Layout.alignment: Qt.AlignHCenter
            }
            TapHandler{
                onTapped: {
                    rect_all.visible=true
                    rect_photo.visible=false
                    rect_video.visible=false
                }
            }
        }
        ColumnLayout{
            id:photo
            Text{
                font.italic: true
                font.bold: true
                font.pixelSize: 30
                Layout.alignment: Qt.AlignHCenter
                text: qsTr("照片")
            }
            Rectangle{
                id:rect_photo
                width: 30
                height: 5
                radius: 5
                color: "#000000"
                visible: false
                Layout.alignment: Qt.AlignHCenter
            }
            TapHandler{
                onTapped: {
                    rect_all.visible=false
                    rect_photo.visible=true
                    rect_video.visible=false
                }
            }
        }
        ColumnLayout{
            id:video
            Text{
                font.italic: true
                font.bold: true
                font.pixelSize: 30
                Layout.alignment: Qt.AlignHCenter
                text: qsTr("视频")
            }
            Rectangle{
                id:rect_video
                width: 30
                height: 5
                radius: 5
                color: "#000000"
                visible:false
                Layout.alignment: Qt.AlignHCenter
            }
            TapHandler{
                onTapped: {
                    rect_all.visible=false
                    rect_photo.visible=false
                    rect_video.visible=true
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
        height: rootHeight*0.2+materialsListView.height
        anchors.top: seperator_line_2.bottom
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.topMargin: rootWidth*0.02
        anchors.leftMargin: rootWidth*0.03
        anchors.bottomMargin: rootWidth*0.02
        Component{
            id:materialComponent
            Rectangle{
                id: jot
                width:rootWidth*0.3
                height: width
                border.color: "#000000"
                border.width:1
                radius: 5
                Image{
                    width:parent.width
                    height: parent.height
                    source: materialData[index].path
                    Rectangle{
                        radius: 90
                        width: parent.width*0.2
                        height: width
                        border.width: 1
                        border.color: "grey"
                        anchors.top: parent.top
                        anchors.right: parent.right
                        anchors.margins: parent.width*0.02
                        Text{
                            id:num_material
                            anchors.centerIn: parent
                            text: qsTr(materialData[index].order)
                        }
                    }
                }

                TapHandler{
                    onTapped: {
                        if(!materialData[index].isSelected){
                            if(materialCount<9){
                                materialData[index].isSelected=true
                                materialData[index].order=""+(++materialCount)
                                num_material.text=qsTr(""+materialCount)
                                selectMaterialData.push({"path":materialData[index].path})
                            }else{
                                toast.show("Can't choose anymore")
                            }
                        }else{
                            --materialCount
                            materialData[index].isSelected=false
                            materialData[index].order=""
                            resortMaterial(num_material.text)
                            num_material.text=qsTr("")
                        }
                        changePrimeStyle()
                    }
                }
            }
        }

        GridView {
            id: materialsListView
            width: rootWidth
            height: rootHeight
            cellWidth: rootWidth*0.32
            cellHeight: cellWidth
            model: materialData
            delegate: materialComponent
            clip: true
        }
    }
}
