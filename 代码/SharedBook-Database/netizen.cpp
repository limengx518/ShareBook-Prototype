#include "netizen.h"
#include "materialbroker.h"
#include "jottingbroker.h"
#include <iostream>

Netizen::Netizen()
{

}

Netizen::Netizen(int id,QString nickname, QString avatar,QString signal)
{
    this->m_id = id;
    this->m_nickname = nickname;
    this->m_avatar = avatar;
    this->m_signal = signal;
}

int Netizen::getID()
{
    return this->m_id;
}

void Netizen::get_Netizen_ID_Info()
{
    //nickname signal avatar

//     qDebug()<<"....网民的ID信息....";
     qDebug()<<"昵称："<<this->m_nickname<<"  "<<"头像："<<this->m_avatar;
}

void Netizen::get_Fans_ID_Info()
{
     qDebug()<<"\n....得到该网民的粉丝所有ID信息....";
    for(auto & fan:this->m_fans){
        fan->get_Netizen_ID_Info();
    }
}

void Netizen::setInterests(QVector<Netizen*> interests)
{
    this->m_interests = interests;
}

QVector<Netizen*> Netizen::getInterests()
{
    return m_interests;

}

void Netizen::get_Interests_ID_Info()
{
     qDebug()<<"\n....得到该网民关注的人的所有ID信息....";
    for(auto & interest:this->m_interests){
        interest->get_Netizen_ID_Info();
    }
}

QString Netizen::getNickname()
{
    return this->m_nickname;
}

void Netizen::pushInterestsJotting(NetizenBroker *nb,JottingBroker *jb,MaterialBroker *mb)
{
    //According to the ID of the person interested in netizens,
    //find all Jottings published by the person interested in through JottingBroker
    //get the digest of the Jottings.
    for(auto & interest: this->m_interests){
        QVector<Jotting*> tempJottings=jb->findNetizenJotById(interest->getID());
        interest->setJottings(tempJottings);
        interest->getAllJotDig(nb,mb,jb);
    }
}

//
void Netizen::getAllJotDig(NetizenBroker *nb, MaterialBroker *mb,JottingBroker *jb)
{
    qDebug()<<"\n....得到网民所有的笔记摘要....\n";
    for(auto & jot: this->m_jottings){
        jot->getJotDig(nb,mb,jb);
    }
}

void Netizen::setJottings(QVector<Jotting*> jottings)
{
    this->m_jottings = jottings;
//    for(auto &jotting: m_jottings){
//        jotting.setPublisher(this);
//    }
}

void Netizen::setFans(QVector<Netizen*> fans)
{
    this->m_fans = fans;
}

QVector<Netizen*> Netizen::getFans()
{
    return this->m_fans;
}
