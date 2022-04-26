#include "jotting.h"
#include "commentbroker.h"
#include "netizen.h"
#include "materialbroker.h"
#include <iostream>
#include "jottingbroker.h"

Jotting::Jotting(int id,QString time,QString text,Netizen *publisher,Material *material)
{
    this->m_id = id;
    this->m_time = time;
    this->m_material = material;
    this->m_publisher = publisher;
    this->m_text = text;
}

//
void Jotting::getJotDig(NetizenBroker *nb,MaterialBroker *mb,JottingBroker * jb)
{
//     qDebug()<<"得到一篇笔记的摘要:";
    //Judge whether the Jotting is associated with the publisher.
    qDebug()<<this->m_time<<"   "<<this->m_text<<"   ";
    if(this->m_publisher == nullptr){
        setPublisher(nb->findNetizenById(jb->findJotPublisher(this->m_id)));
    }
    if(this->m_material==nullptr){
        setMaterial(mb->findMaterialById(jb->findMatrialByID(this->m_id)));
    }

     m_material->getMaterialDig();
     m_publisher->get_Netizen_ID_Info();
     qDebug()<<" ";


}

int Jotting::getID()
{
    return this->m_id;
}

void Jotting::setId(int id)
{
    this->m_id = id;
}

void Jotting::addNewComment(JottingBroker* jb,Comment *comment)
{
    m_comments.append(comment);
    //jb->update(this)
}

void Jotting::setMaterial(Material *material)
{
    this->m_material = material;
    //    m_material->setJotting(this);
}

void Jotting::getTheJotDetail(NetizenBroker* nb,CommentBroker* cb)
{
    qDebug()<<"发布时间："<<this->m_time<<"   "<<" 文本内容："<<this->m_text<<"   ";

    //Concurrent operation
    //A:
    m_material->getMaterialDetail();


    if(m_comments.size()==0){
        setComment(cb->findJotComment(m_id));
    }

    //B:
    qDebug()<<"所有评论信息：";
    for(auto &comment:m_comments)
        comment->getCommentDetail(nb,cb);
}

Netizen Jotting::getPublisher()
{
    return *m_publisher;
}

void Jotting::setPublisher(Netizen *publisher)
{
    this->m_publisher = publisher;
}

void Jotting::setComment(QVector<Comment *> comments)
{
    m_comments=comments;
}
