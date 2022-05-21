#include "jotting.h"
#include <nlohmann/json.hpp>
#include <iostream>
#include <functional>
#include <utility>

using json = nlohmann::json;

Jotting::Jotting(const std::string &tid, std::string netizenId):
    JottingInterface(tid),_netizenProxy(netizenId),m_note{}
{
}

Jotting::Jotting(const std::string id, std::string content,std::string netizenId, std::vector<std::string> materialsId):
    JottingInterface(id),_netizenProxy(netizenId),m_note{content}
{
    for(const auto& item:materialsId){
        _materials.insert(std::pair<std::string,MaterialProxy>(item,MaterialProxy(item)));
    }
}


nlohmann::json Jotting::getAbstract()
{
    json j;
    j["content"]=m_note;
    j["material_firstPath"]=_materials.begin()->second.getMaterialAbstract();
    j["netizen"]=_netizenProxy.getNetizenAbstract();
    return j;
}
