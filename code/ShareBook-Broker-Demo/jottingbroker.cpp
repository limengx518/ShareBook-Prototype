#include "jottingbroker.h"
#include <unordered_map>
#include <sstream>
#include <string>
#include <vector>

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
    Jotting* jotting=inCache(id);
    if(jotting == nullptr){
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

        storeObject(*jotting);
        return jotting;
    }
    std::cout<<"in cache"<<std::endl;
    return jotting;
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

Jotting* JottingBroker::inCache(std::string objectId)
{
    std::unordered_map<std::string,std::string> m=RelationalBroker::inCache("jotting"+objectId);
    if(m.empty())
        return nullptr;
    std::stringstream materialsId(m["materialId"]);
    std::string id;
    std::vector<std::string> materials;
    while(std::getline(materialsId,id,',')){
        materials.push_back(id);
    }
    Jotting* jotting=new Jotting(objectId,m["note"],m["netizenId"],materials);

    return jotting;
}

void JottingBroker::storeObject(const Jotting &jotting)
{
    std::vector<std::string> vector=jotting.materialId();
    std::string materialsId="";
    for(const auto &item:vector){
        materialsId+=item;
        materialsId+=",";
    }
    std::unordered_map<std::string,std::string> map{
        {"note", jotting.note()},
        {"netizenId", jotting.netizenId()},
        {"materialId",materialsId}
    };
    RelationalBroker::storeObject("jotting"+jotting.id(),map);
}

JottingBroker::JottingBroker()
{

}
