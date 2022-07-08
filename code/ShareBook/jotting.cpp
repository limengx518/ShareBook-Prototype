#include "jotting.h"
#include "jottingbroker.h"
#include <nlohmann/json.hpp>
#include <iostream>
#include <functional>
#include <utility>

using json = nlohmann::json;

Jotting::Jotting(const std::string &tid, std::string netizenId):
    JottingInterface(tid),_netizenProxy(netizenId),m_content{}
{
}

Jotting::Jotting(const std::string id, std::string content, std::string time, std::string netizenId, std::vector<std::string> materialsId, std::vector<std::string> commentsId):
    JottingInterface(id),_netizenProxy(netizenId),m_time{time},m_content{content}
{
    for(const auto& item:materialsId){
        _materials.insert(std::pair<std::string,MaterialProxy>(item,MaterialProxy(item)));
    }
    for(const auto& item:commentsId){
        _comments.insert(std::pair<std::string,CommentProxy>(item,CommentProxy(item)));
    }
}


nlohmann::json Jotting::getAbstract()
{
    json j;
    j["content"]=m_content;
    j["time"]=m_time;
    if(!_materials.empty())
        j["material_firstPath"]=_materials.begin()->second.getAbstract();
    j["netizen"]=_netizenProxy.getAbstract();
    return j;
}

nlohmann::json Jotting::getDetail()
{
    json j;
    j["content"]=m_content;
    j["time"]=m_time;
    j["netizen"]=_netizenProxy.getAbstract();
    for(auto& item:_comments){
        j["comments"][item.first]=item.second.getInfo();
    }
    for(auto& item:_materials){
        j["materials"][item.first]=item.second.getAbstract();
    }
    return j;

}

const std::string Jotting::note() const
{
    return m_content;
}

const std::string Jotting::time() const
{
    return m_time;
}

const std::string Jotting::netizenId() const
{
    return _netizenProxy.id();
}

const std::vector<std::string> Jotting::commentId()
{
    std::vector<std::string> vector;
    for(const auto &item:_comments){
        vector.push_back(item.first);
    }
    return vector;
}

const std::vector<std::string> Jotting::materialId() const
{
    std::vector<std::string> vector;
    for(const auto &item:_materials){
        vector.push_back(item.first);
    }
    return vector;
}

const std::vector<std::string> Jotting::commentId() const
{
    std::vector<std::string> vector;
    for(const auto &item:_comments){
        vector.push_back(item.first);
    }
    return vector;
}

void Jotting::comment(const std::string commentId)
{
    _comments.insert(std::pair<std::string,CommentProxy>(commentId, CommentProxy(commentId)));
    JottingBroker::getInstance()->cleanToDirtyState(id());
//     JottingBroker::getInstance()->delete();
}

