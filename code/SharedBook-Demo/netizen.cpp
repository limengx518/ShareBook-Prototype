#include "netizen.h"
#include "materialbroker.h"
#include "jottingbroker.h"
#include <iostream>


Netizen::Netizen()
{

}

Netizen::Netizen(int id,std::string nickname, std::string avatar,std::string signal)
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

    std::cout<<"网民的ID信息:  ";
    std::cout<<"昵称："<<this->m_nickname<<"  ";
    std::cout<<"头像："<<this->m_avatar<<std::endl;
}

void Netizen::get_Fans_ID_Info()
{
    std::cout<<"得到该网民的粉丝所有ID信息"<<std::endl;
    for(auto & fan:this->m_fans){
        fan.get_Netizen_ID_Info();
    }
}

void Netizen::setInterests(std::vector<Netizen> interests)
{
    this->m_interests = interests;
}

std::vector<Netizen> Netizen::getInterests()
{
    return m_interests;

}

void Netizen::get_Interests_ID_Info()
{
    std::cout<<"得到该网民关注的人的所有ID信息"<<std::endl;
    for(auto & interest:this->m_interests){
        interest.get_Netizen_ID_Info();
    }
}

std::string Netizen::getNickname()
{
    return this->m_nickname;
}

void Netizen::pushInterestsJotting(NetizenBroker *nb,JottingBroker *jb,MaterialBroker *mb)
{
    //According to the ID of the person interested in netizens,
    //find all Jottings published by the person interested in through JottingBroker
    //get the digest of the Jottings.
    for(auto & interest: this->m_interests){
        std::vector<Jotting> tempJottings=jb->find_Netizen_Jottings(interest.getID());
        interest.setJottings(tempJottings);
        interest.getAllJotDig(nb,mb);
    }
}

//
void Netizen::getAllJotDig(NetizenBroker *nb, MaterialBroker *mb)
{

    std::cout<<"得到网民所有的笔记摘要:"<<std::endl;
    for(auto & jot: this->m_jottings){
        jot.getJotDig(nb,mb);
    }
}

void Netizen::setJottings(std::vector<Jotting> jottings)
{
    this->m_jottings = jottings;
//    for(auto &jotting: m_jottings){
//        jotting.setPublisher(this);
//    }
}

void Netizen::setFans(std::vector<Netizen> fans)
{
    this->m_fans = fans;
}

std::vector<Netizen> Netizen::getFans()
{
    return this->m_fans;
}
