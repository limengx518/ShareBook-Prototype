#include "netizenproxy.h"
#include "netizenbroker.h"
#include "netizen.h"

NetizenProxy::NetizenProxy(const std::string &tid):
    NetizenInterface(tid),_netizen(nullptr)
{
}

NetizenProxy::~NetizenProxy()
{
    if(_netizen!=nullptr)
        delete _netizen;
}

nlohmann::json NetizenProxy::getNetizenAbstract()
{
    if(_netizen==nullptr){
        _netizen=&NetizenBroker::getInstance()->findNetizenById(id());
    }
    return _netizen->getNetizenAbstract();
}
