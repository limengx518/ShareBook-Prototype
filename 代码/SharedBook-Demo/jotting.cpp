#include "jotting.h"
#include "netizen.h"
#include "materialbroker.h"
#include <iostream>

Jotting::Jotting(int id,std::string time,std::string text,Netizen *publisher,Material *material)
{
    this->m_id = id;
    this->m_time = time;
    this->m_material = material;
    this->m_publisher = publisher;
    this->m_text = text;
}

//
void Jotting::getJotDig(NetizenBroker *nb,MaterialBroker *mb)
{
    std::cout<<"得到一篇笔记的摘要:";
    //Judge whether the Jotting is associated with the publisher.
    if(this->m_publisher == nullptr){
        setPublisher( nb->findNetizenByID(getID()));
    }

//    setMaterial(mb->findMaterialByID(getID()));
    m_publisher->get_Netizen_ID_Info();
    m_material->getMaterialDig();
    std::cout<<this->m_time<<"   "<<this->m_text<<"   "<<std::endl;


}

int Jotting::getID()
{
    return this->m_id;
}

void Jotting::setMaterial(Material *material)
{
    this->m_material = material;
//    m_material->setJotting(this);
}

Netizen Jotting::getPublisher()
{
    return *m_publisher;
}

void Jotting::setPublisher(Netizen *publisher)
{
    this->m_publisher = publisher;
}
