#include "netizenbroker.h"
#include "netizen.h"
#include <iostream>

NetizenBroker::NetizenBroker()
{
}

Netizen *NetizenBroker::findNetizenByID(int netizenId)
{
    for(auto & netizen:m_netizens){
        if(netizen.getID() == netizenId){
            return &netizen;
        }
    }
    return nullptr;
}

std::vector<Netizen> NetizenBroker::findFansByID(int netizenId)
{
//    std::vector<Netizen> result;
    std::cout<<"查找网民的所有粉丝ID"<<std::endl;
    Netizen *nt = findNetizenByID(netizenId);
    return nt->getFans();
//    for(auto & netizen:m_netizens){
//        std::vector<Netizen> interest=netizen.getInterests();
//        for(auto in:interest){
//            if(in.getID()==netizenId){
//                result.push_back(in);
//                break;
//            }
//        }
//    }
}

std::vector<Netizen> NetizenBroker::findInterestsByID(int netizenId)
{
    std::cout<<"查找网民的所有关注者ID"<<std::endl;
    Netizen *nt = findNetizenByID(netizenId);
    return nt->getInterests();
}

void NetizenBroker::setNetizens(std::vector<Netizen> netizens)
{
    this->m_netizens = netizens;
}
