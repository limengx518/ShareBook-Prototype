#include "jottingbroker.h"
#include "jotting.h"
#include "netizen.h"
#include <iostream>

JottingBroker::JottingBroker()
{

}

std::vector<Jotting> JottingBroker::find_Netizen_Jottings(int netizenId)
{
    std::cout<<"查找网民的所有笔记："<<std::endl;
    std::vector<Jotting> result;
    for(auto & jotting: m_jottings){
        if(jotting.getPublisher().getID() == netizenId){
            result.push_back(jotting);
        }
    }
    return result;
}

std::vector<Jotting> JottingBroker::findSomeJottings()
{

}

void JottingBroker::setJottings(std::vector<Jotting> jottings)
{
    this->m_jottings = jottings;
}

std::vector<Jotting> JottingBroker::getJottings()
{
    return m_jottings;
}
