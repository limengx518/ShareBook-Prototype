#include "netizenbroker.h"

NetizenBroker* NetizenBroker::m_netizenBroker=NULL;

NetizenBroker *NetizenBroker::getInstance()
{
    if(m_netizenBroker==nullptr){
        m_netizenBroker=new NetizenBroker();
    }
    return m_netizenBroker;
}

Netizen &NetizenBroker::findNetizenById(std::string id)
{
    auto search = _netizensCache.find(id);
    if(search == _netizensCache.end()){
        //retrieveJotting(id)
        Netizen netizen=*(RelationalBroker::findNetizenById(id));
        _netizensCache.insert(std::pair<std::string,Netizen>(id,netizen));
    }
    return _netizensCache.at(id);
}

NetizenBroker::~NetizenBroker()
{
    if(m_netizenBroker!=nullptr)
        delete m_netizenBroker;
}

NetizenBroker::NetizenBroker()
{

}
