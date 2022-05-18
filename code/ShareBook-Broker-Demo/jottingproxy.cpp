#include "jottingproxy.h"
#include "jotting.h"
#include "jottingbroker.h"

JottingProxy::JottingProxy(const std::string &tid):
    JottingInterface{tid},_jotting(nullptr)
{
}

JottingProxy::~JottingProxy()
{
    if(_jotting!=nullptr)
        delete _jotting;
}


nlohmann::json JottingProxy::getJottingAbstract()
{
    if(_jotting==nullptr){
        _jotting=new Jotting(JottingBroker::getInstance()->findJottingById(id()));
    }
     return _jotting->getJottingAbstract();
}
