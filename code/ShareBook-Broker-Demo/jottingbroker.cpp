#include "jottingbroker.h"

JottingBroker* JottingBroker::m_jottingBroker=NULL;

JottingBroker *JottingBroker::getInstance()
{
    if(m_jottingBroker==nullptr){
        m_jottingBroker=new JottingBroker();
    }
    return m_jottingBroker;
}

Jotting *JottingBroker::findById(std::string id)
{
    auto search = _jottingsCache.find(id);
    if(search == _jottingsCache.end()){

        std::string command="select * from Jotting where J_id="+id;
        sql::ResultSet* res=RelationalBroker::query(command);
        std::string id,content,nid;
         // Loop through and print results
        while (res->next()) {
            id=std::to_string(res->getInt(1));
            content=res->getString(2);
            nid=std::to_string(res->getInt(3));
        }
        //retrieveJotting(id)
        Jotting *jotting=new Jotting(id,content,nid,findMaterial(id));

        _jottingsCache.insert(std::pair<std::string,Jotting>(id,*jotting));
        return jotting;
    }
    return &_jottingsCache.at(id);
}



void JottingBroker::addNewJotting(Jotting *jotting)
{
    _jottingsCache.insert(std::pair<std::string,Jotting>(jotting->id(),*jotting));
}

std::vector<std::string> JottingBroker::findMaterial(std::string id)
{
    std::vector<std::string> materialIds;
std::string com="select M_id from Material where J_id="+id;
    sql::ResultSet* res=RelationalBroker::query(com);
    while (res->next()) {
        materialIds.push_back(std::to_string(res->getInt(1)));
    }
    return materialIds;
}

JottingBroker::JottingBroker()
{

}
