#include "netizen.h"
#include "comment.h"
#include "time.h"
#include "jottingbroker.h"
#include "netizenbroker.h"
#include "jottingproxy.h"
#include "timeInfo.h"
#include <unordered_map>
#include <iostream>
#include "commentproxy.h"
#include "commentbroker.h"
#include <iostream>
#include <fstream>

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

nlohmann::json Netizen::getInfo()
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
//    std::cout<<netizenInfo.dump(4)<<std::endl;

    return netizenInfo;
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

const std::string Netizen::readLog()
{
    std::string line,last_line;
    int lineNumber=0,i=0;
    std::ifstream logFile;
    logFile.open("/temp/log.txt");

    while(std::getline(logFile,line))
        lineNumber++;

    logFile.clear();
    logFile.seekg(0);

    while(std::getline(logFile,last_line) && i<lineNumber-2)
        i++;

    logFile.close();
//    std::cout<<"line="<<last_line<<std::endl;
    last_line = last_line.substr(4,last_line.length()-1);
    return last_line;
}

void Netizen::writeLog()
{
    std::string time_string=getTime();
    std::ofstream logFile;
    logFile.open("/temp/log.txt",std::ios::out|std::ios::app);
    logFile<<"in:"<<time_string<<std::endl;
}

nlohmann::json Netizen::scanJottings()
{
    std::vector<JottingProxy> jottingProxys=JottingBroker::getInstance()->pushJottings(id(),readLog(),getTime());
    json jottings;
    for(auto &item:jottingProxys){
        jottings[item.id()]=item.getAbstract();
    }
    return jottings;
}

nlohmann::json Netizen::checkOneJotting(std::string jottingId)
{
    Jotting *jotting=JottingBroker::getInstance()->findById(jottingId);
    return jotting->getDetail();
}

bool Netizen::comment(const std::string content, const std::string jottingId)
{

    std::string time=getTime();
    time.erase(std::find(time.begin(), time.end(), '-'));
    time.erase(std::find(time.begin(), time.end(), '-'));
    Comment comment(time,content,id(),jottingId);

    CommentBroker::getInstance()->addComment(comment);
    _comments.insert(std::pair<std::string,CommentProxy>(comment.id(), CommentProxy(comment.id())));

    Jotting *jotting=JottingBroker::getInstance()->findById(jottingId);
    jotting->comment(comment.id());

//    NetizenBroker::getInstance()->remove(id());

    return true;
}


