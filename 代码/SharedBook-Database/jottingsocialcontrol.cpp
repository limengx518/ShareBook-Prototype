#include "jottingbroker.h"
#include "materialbroker.h"
#include "netizenbroker.h"
#include "commentbroker.h"
#include "netizen.h"

#include "jottingsocialcontrol.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <QDateTime>

JottingSocialControl::JottingSocialControl(){
    this->nb =  NetizenBroker::getInstance();
    this->jb = JottingBroker::getInstance();
    this->cb =CommentBroker::getInstance();
    this->mb = MaterialBroker::getInstance();

//    Init();

}


void JottingSocialControl::login(int id)
{
    //The controller finds netize's all information according to netizen acount.
    m_netizen = nb->findNetizenById(id);
    m_netizen->get_Netizen_ID_Info();

    //Concurrent operation
    //According to the ID information of netizens, find the Jottings published by netizens
    //from the JottingBroker,and set them to the Netizen class.
    //get the degist of all jottings.

    //A:
    m_netizen->setJottings(jb->findNetizenJotById(m_netizen->getID()));
    m_netizen->getAllJotDig(nb,mb,jb);

    //According to the ID of the netizen, find the fans and interests
    //of the netizen through the NetizenBroker.

    //B:
    m_netizen->setFans(nb->findFans(m_netizen->getID()));
    m_netizen->get_Fans_ID_Info();

    //C:
    m_netizen->setInterests(nb->findInterests(m_netizen->getID()));
    m_netizen->get_Interests_ID_Info();

}

void JottingSocialControl::pushJottings()
{
    //Concurrent operation
    //A: Find Jottings published by netizen's interests and push them
    qDebug()<<"\n....随机推送笔记....";
//    m_jottings.append(m_netizen->pushInterestsJotting(jb));

    qDebug()<<" ";
    //B:Find the Jottings published in the system and push them randomly
    m_jottings=jb->findSomeJottings();

    for(auto jotting: m_jottings){
        jotting->getJotDig(nb,mb,jb);
    }

}

void JottingSocialControl::checkOneJot(int index)
{
    qDebug()<<"\n....选择某个笔记详细查看：....";
    m_scanJotting=findJot(index);
    m_scanJotting->getTheJotDetail(nb,cb);
}

Jotting *JottingSocialControl::findJot(int index)
{
    return m_jottings[index];
}

void JottingSocialControl::commentTheJot(QString content)
{
    Comment* comment=new Comment(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"),content,m_netizen,m_scanJotting);
    //Concurrent operation

    //A:cb->addNewComment(Comment* comment)

    //B:
    m_netizen->addPostedCom(nb,comment);

    //C:
    m_scanJotting->addNewComment(jb,comment);


}


