#include "jottingproxy.h"
#include "jotting.h"
#include "jottingbroker.h"

JottingProxy::JottingProxy(const std::string &tid):
    JottingInterface{tid},_jotting(nullptr)
{
}

JottingProxy::~JottingProxy()
{
}


nlohmann::json JottingProxy::getAbstract()
{
    if(_jotting == nullptr){
        _jotting = JottingBroker::getInstance()->findById(id());
    }
     return _jotting->getAbstract();
}
