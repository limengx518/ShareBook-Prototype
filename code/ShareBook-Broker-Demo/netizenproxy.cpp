#include "netizenproxy.h"
#include "netizenbroker.h"
#include "netizen.h"

NetizenProxy::NetizenProxy(const std::string &tid):
    NetizenInterface(tid),_netizen(nullptr)
{
}

NetizenProxy::~NetizenProxy()
{
}

nlohmann::json NetizenProxy::getNetizenAbstract()
{
    if(_netizen==nullptr){
        _netizen=NetizenBroker::getInstance()->findById(id());
    }
    return _netizen->getNetizenAbstract();
}
