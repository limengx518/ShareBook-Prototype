#include "netizen.h"
#include "jottingproxy.h"
#include <unordered_map>
#include <iostream>

using json = nlohmann::json;

Netizen::Netizen(const std::string &tid):
    NetizenInterface(tid)
{

}

Netizen::Netizen(const std::string id, std::string nickName, std::vector<std::string> jottingId,std::vector<std::string> fansId,std::vector<std::string> concernedsId):
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
}

void Netizen::getInfo()
{
    json netizenInfo;
    netizenInfo["name"]=m_nickName;
    for(auto &jp:_jottings){
        json jotting=jp.second.getAbstract();
        netizenInfo["jottings"][jp.first]["netizen"]=jotting["netizen"];
        netizenInfo["jottings"][jp.first]["content"]=jotting["content"];
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

std::string Netizen::nickName()
{
    return m_nickName;
}

nlohmann::json Netizen::getAbstract()
{
    json j;
    j["nickName"]=m_nickName;
    return j;
}
