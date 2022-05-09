#include "material.h"
#include "jotting.h"
#include "picture.h"
#include "video.h"
#include "audio.h"
#include <iostream>

Material::Material(int id, QVector<Picture *> picture, Audio *audio, Video *video)
{
    this->m_materialId=id;
    this->m_pictures=picture;
    this->m_audio=audio;
    this->m_video=video;
}

Material::Material(QVector<Picture *> picture, Audio *audio, Video *video)
{
    this->m_pictures=picture;
    this->m_audio=audio;
    this->m_video=video;
}

void Material::getMaterialDetail()
{
    qDebug()<<"所有素材信息：";
    if(m_pictures.size()!=0){
        for(auto item:m_pictures)
            qDebug()<<"...图片信息："<<item->getContent();
    }
    if(m_video!=nullptr){
        qDebug()<<"...音频信息："<<m_video->getContent();
    }
    if(m_audio!=nullptr){
        qDebug()<<"...视频信息："<<m_audio->getContent();
    }
}

void Material::getMaterialDig()
{
//    for(auto & pic:this->m_materials)
//         qDebug()<<pic<<"  ";
    qDebug()<<"素材摘要信息：";
    if(m_pictures.size()>0){
        qDebug()<<"..."<<m_pictures[0]->getContent();
    }
    if(m_audio!=nullptr) qDebug()<<"..."<<m_audio->getContent();
    if(m_video!=nullptr) qDebug()<<"..."<<m_video->getContent();
}

void Material::setJotting(Jotting *jot)
{
    this->m_jotting = jot;
}

int Material::getMaterialId()
{
    return this->m_materialId;
}

void Material::adapt()
{
    qDebug()<<"调整素材";
//    m_audio = nullptr;
}

QVector<Picture *> Material::getPictures()
{
    return m_pictures;
}

Audio *Material::getAudio()
{
    return m_audio;
}

Video *Material::getVideo()
{
    return m_video;
}
