#include "materialbroker.h"
#include "picture.h"
#include "audio.h"
#include "video.h"
#include "material.h"
#include <QDebug>

MaterialBroker* MaterialBroker::materialBroker=NULL;

Material* MaterialBroker::findMaterialById(int id) const
{
//    QHash<QString,QString> map=db->findMaterialById(id);

    Material* ma=new Material();
    return ma;

}


Picture *MaterialBroker::findPictureById(int picture_id)
{
    QString commend;
    commend="select * from Picture where P_id="+QString::number(picture_id);
    QHash<QString,QString> map=db->findMaterialById(commend);

//    qDebug()<<"id: "<<map.value("id")<<"content: "<<map.value("content");

    Picture* ma=new Picture(map.value("id").toInt(),map.value("content"));
    return ma;
}

Audio *MaterialBroker::findAudioById(int audio_id)
{
    QString commend;
    commend="select * from Audio where A_id="+QString::number(audio_id);
    QHash<QString,QString> map=db->findMaterialById(commend);

//    qDebug()<<"id: "<<map.value("id")<<"content: "<<map.value("content");

    Audio* ma=new Audio(map.value("id").toInt(),map.value("content"));
    return ma;
}

Video *MaterialBroker::findVideoById(int video_id)
{
    QString commend;
    commend="select * from Video where V_id="+QString::number(video_id);
    QHash<QString,QString> map=db->findMaterialById(commend);

//    qDebug()<<"id: "<<map.value("id")<<"content: "<<map.value("content");

    Video* ma=new Video(map.value("id").toInt(),map.value("content"));
    return ma;
}

Material* MaterialBroker::findJotMaterial(int jotting_id)
{
    QHash<QString,QVector<QString>> map=db->findJotMaterial(jotting_id);

    Audio* audio = nullptr;
    Video* video = nullptr;
    QVector<Picture*> pictures;
    QHash<QString,QVector<QString>>::Iterator i;
    for(i=map.begin(); i!=map.end(); ++i){
        if(i.key()=="Picture"&&!i.value().isEmpty()){
            for(int j=0;j<i.value().size();j++){
                pictures.append(findPictureById(i.value()[j].toInt()));
            }
        }else if(i.key()=="Audio"&&!i.value().isEmpty()){
            audio=findAudioById(i.value()[0].toInt());
        }else if(i.key()=="Video"&&!i.value().isEmpty()){
            video=findVideoById(i.value()[0].toInt());
        }
    }

    Material *material=new Material(jotting_id,pictures,audio,video);

    return material;
}

void MaterialBroker::addNewJotMaterial(Material *material, int j_id) const
{
     QString insertCommend;
    if(!material->getPictures().isEmpty()){
        QVector<Picture*> pictures=material->getPictures();
        for(auto picture:pictures){
            insertCommend=QString("insert into Picture (P_content,J_id) values('%1',%2)").arg(picture->getContent()).arg(j_id);
            db->insertData(insertCommend);
        }
    }
    if(material->getAudio()){
        Audio* audio=material->getAudio();
        qDebug()<<audio->getContent();
        insertCommend=QString("insert into Audio (A_content,J_id) values('%1',%2)").arg(audio->getContent()).arg(j_id);
        db->insertData(insertCommend);
    }
    if(material->getVideo()){
        Video* video=material->getVideo();
        insertCommend=QString("insert into Video (V_content,J_id) values('%1',%2)").arg(video->getContent()).arg(j_id);
        db->insertData(insertCommend);
    }
}

