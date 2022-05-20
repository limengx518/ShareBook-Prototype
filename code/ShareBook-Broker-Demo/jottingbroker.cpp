#include "jottingbroker.h"

JottingBroker* JottingBroker::m_jottingBroker=NULL;

JottingBroker *JottingBroker::getInstance()
{
    if(m_jottingBroker==nullptr){
        m_jottingBroker=new JottingBroker();
    }
    return m_jottingBroker;
}

Jotting &JottingBroker::findJottingById(std::string id)
{
    auto search = _jottingsCache.find(id);
    if(search == _jottingsCache.end()){
        //retrieveJotting(id)
        Jotting jotting=*(RelationalBroker::findJottingById(id));
        _jottingsCache.insert(std::pair<std::string,Jotting>(id,jotting));
    }
    return _jottingsCache.at(id);
}

std::vector<std::string> JottingBroker::getSomeJottingsId(std::string lastTime, std::string thisTime)
{
    std::vector<std::string>idVector;
    for(auto &jotting:RelationalBroker::findSomeJottings(lastTime,thisTime)){
        _jottingsCache.insert(std::pair<std::string,Jotting>(jotting->id(),*jotting));
        idVector.push_back(jotting->id());
    }
    return idVector;
}

void JottingBroker::addNewJotting(Jotting *jotting)
{
    _jottingsCache.insert(std::pair<std::string,Jotting>(jotting->id(),*jotting));
}

JottingBroker::JottingBroker()
{

}
