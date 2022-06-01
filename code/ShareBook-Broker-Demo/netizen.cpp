#include "netizen.h"
#include "jottingproxy.h"
#include <unordered_map>
#include <iostream>
#include "commentproxy.h"

using json = nlohmann::json;

Netizen::Netizen(const std::string &tid):
    NetizenInterface(tid)
{

}

Netizen::Netizen(const std::string id, std::string nickName, std::vector<std::string> jottingId, std::vector<std::string> fansId, std::vector<std::string> concernedsId, std::vector<std::string> commentdId):
    NetizenInterface(id),m_nickName(nickName)
{
    for(auto &jId:jottingId){
         _jottings.insert(std::pair<std::string,JottingProxy>(jId, JottingProxy(jId)));
    }
    for(auto &fId:fansId){
         _fans.insert(std::pair<std::string,NetizenProxy>(fId, NetizenProxy(fId)));
    }
    for(auto &cId:concernedsId){
        _concerneds.insert(std::pair<std::string,NetizenProxy>(cId, NetizenProxy(cId)));
    }
    for(auto &cId:commentdId){
        _comments.insert(std::pair<std::string,CommentProxy>(cId, CommentProxy(cId)));
    }
}

void Netizen::getInfo()
{
    json netizenInfo;
    netizenInfo["name"]=m_nickName;
    for(auto &jp:_jottings){
        json jotting=jp.second.getAbstract();
        netizenInfo["jottings"][jp.first]["netizen"]=jotting["netizen"];
        netizenInfo["jottings"][jp.first]["content"]=jotting["content"];
        netizenInfo["jottings"][jp.first]["time"]=jotting["time"];
        netizenInfo["jottings"][jp.first]["material"]=jotting["material_firstPath"];
    }
    for(auto &fp:_fans){
       json netizenAbstract=fp.second.getAbstract();
       netizenInfo["fans"][fp.first]["nickName"]=netizenAbstract["nickName"];
    }
    for(auto &cp:_concerneds){
       json netizenAbstract=cp.second.getAbstract();
       netizenInfo["concerneds"][cp.first]["nickName"]=netizenAbstract["nickName"];
    }
    std::cout<<netizenInfo.dump(4)<<std::endl;
}

const std::string Netizen::nickName()const
{
    return m_nickName;
}

const std::vector<std::string> Netizen::jottings() const
{
    std::vector<std::string> jottings;
    for(const auto& item:_jottings){
        jottings.push_back(item.first);
    }
    return jottings;
}

const std::vector<std::string> Netizen::fans() const
{
    std::vector<std::string> fans;
    for(const auto& item:_fans){
        fans.push_back(item.first);
    }
    return fans;
}

const std::vector<std::string> Netizen::concerneds() const
{
    std::vector<std::string> concerneds;
    for(const auto& item:_concerneds){
        concerneds.push_back(item.first);
    }
    return concerneds;
}

nlohmann::json Netizen::getAbstract()
{
    json j;
    j["nickName"]=m_nickName;
    return j;
}
