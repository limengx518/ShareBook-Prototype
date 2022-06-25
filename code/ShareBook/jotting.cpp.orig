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
    j["material_firstPath"]=_materials.begin()->second.getAbstract();
    j["netizen"]=_netizenProxy.getAbstract();
    return j;
}

const std::string Jotting::note() const
{
    return m_note;
}

const std::string Jotting::netizenId() const
{
    return _netizenProxy.id();
}

const std::vector<std::string> Jotting::materialId() const
{
    std::vector<std::string> vector;
    for(const auto &item:_materials){
        vector.push_back(item.first);
    }
    return vector;
}
