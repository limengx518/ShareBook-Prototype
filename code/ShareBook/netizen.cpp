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
        netizenInfo["jottings"].push_back(jotting);
    }
    netizenInfo["fanCount"]=std::to_string(_fans.size());
    for(auto &fp:_fans){
       json netizenAbstract=fp.second.getAbstract();
       netizenInfo["fans"].push_back(netizenAbstract);
    }
    netizenInfo["concernedCount"]=std::to_string(_concerneds.size());
    for(auto &cp:_concerneds){
       json netizenAbstract=cp.second.getAbstract();
       netizenInfo["concerneds"].push_back(netizenAbstract);
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
    //打开log.txt文件
    logFile.open("/temp/log.txt");

    //得到所有的行数
    while(std::getline(logFile,line))
        lineNumber++;

    //修改状态标志
    logFile.clear();
    //设置输入位置指示器
    logFile.seekg(0);

    //得到倒数第二行中的内容
    while(std::getline(logFile,last_line) && i<lineNumber-2)
        i++;

    //关闭文件
    logFile.close();
//    std::cout<<"line="<<last_line<<std::endl;
    last_line = last_line.substr(4,last_line.length()-1);
    return last_line;
}

void Netizen::writeLog()
{
    std::string time_string=getTime();
    std::ofstream logFile;
    //打开log.txt文件，记录本次登陆时间
    logFile.open("/temp/log.txt",std::ios::app|std::ios::out);
    logFile<<"in:"<<time_string<<std::endl;
    logFile.close();
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
    //获取创建时间
    std::string time=getTime();
    time.erase(std::find(time.begin(), time.end(), '-'));
    time.erase(std::find(time.begin(), time.end(), '-'));

    //创建笔记对象
    Comment *comment=new Comment(time,content,id(),jottingId);

    //将笔记对象存入newCleanCache缓存
    CommentBroker::getInstance()->addComment(*comment);

    //建立netizen和comment的联系，并将netizen将其改为DirtyCache里
    _comments.insert(std::pair<std::string,CommentProxy>(comment->id(), CommentProxy(comment->id())));
    NetizenBroker::getInstance()->cleanToDirtyState(id());

    //建立jotting和comment的联系，并将jotting将其改为DirtyCache里
    Jotting *jotting=JottingBroker::getInstance()->findById(jottingId);
    jotting->comment(comment->id());

//    NetizenBroker::getInstance()->remove(id());

    return true;
}

bool Netizen::publishJotting(std::string content, std::string time)
{
    std::vector<std::string> vec;
    //创建笔记对象
    Jotting* jotting=new Jotting(time,content,time,id(),vec,vec);

     //将笔记对象存入newCleanCache缓存
    JottingBroker::getInstance()->addJotting(*jotting);

    //建立netizen和comment的联系，并将netizen放到DirtyCache
    _jottings.insert(std::pair<std::string,JottingProxy>(jotting->id(),JottingProxy(jotting->id())));
    NetizenBroker::getInstance()->cleanToDirtyState(id());

    return true;
}


