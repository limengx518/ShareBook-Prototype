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
        std::string id,content,nid,time;
         // Loop through and print results
        while (res->next()) {
            id=std::to_string(res->getInt(1));
            content=res->getString(2);
            time=res->getString(3);
            nid=std::to_string(res->getInt(4));
        }
        //retrieveJotting(id)
        Jotting *jotting=new Jotting(id,content,time,nid,findMaterials(id),findComments(id));

        //将从数据库中拿出的数据放在缓存中(旧的净缓存)
        oldClean.insert({jotting->id(),std::make_pair(*jotting,0)});

        return jotting;
    }
    std::cout<<"in cache"<<std::endl;
    return jotting;
}

std::vector<JottingProxy> JottingBroker::pushJottings(std::string netizenId, std::string lastTime, std::string thisTime)
{
    std::cout<<"lastTime:"<<lastTime<<std::endl;
    std::cout<<"thisTime:"<<thisTime<<std::endl;
    std::string command="select * from Jotting where J_time BETWEEN '"+lastTime + "' AND '"+thisTime+"'";
    sql::ResultSet* res=RelationalBroker::query(command);
    std::string id;
    std::vector<JottingProxy> ids;
     // Loop through and print results
    while (res->next()) {
        id=std::to_string(res->getInt(1));
        ids.push_back(JottingProxy(id));
    }
    return ids;
}


std::vector<std::string> JottingBroker::findMaterials(std::string jottingId)
{
    std::vector<std::string> materialIds;
std::string com="select M_id from Material where J_id="+jottingId;
    sql::ResultSet* res=RelationalBroker::query(com);
    while (res->next()) {
        materialIds.push_back(std::to_string(res->getInt(1)));
    }
    return materialIds;
}

std::vector<std::string> JottingBroker::findComments(std::string jottingId)
{
    std::vector<std::string> commentIds;
std::string com="select C_id from Comment where J_id="+jottingId;
    sql::ResultSet* res=RelationalBroker::query(com);
    while (res->next()) {
        commentIds.push_back(std::to_string(res->getInt(1)));
    }
    return commentIds;
}

Jotting* JottingBroker::inCache(std::string id)
{
    if(oldClean.find(id)!=oldClean.end()){
        //返回jotting的引用
        return &oldClean.find(id)->second.first;
    }

//    if(oldDirty.find(id)!=oldDirty.end()){
//        //返回jotting的引用
//        return &oldDirty.find(id)->second.first;
//    }

    if(newClean.find(id)!=newClean.end()){
        //返回jotting的引用
        return &newClean.find(id)->second.first;
    }

//    if(newDirty.find(id)!=newDirty.end()){
//        //返回jotting的引用
//        return &newDirty.find(id)->second.first;
//    }

    return nullptr;
}

void JottingBroker::update()
{
    //判断是否需要更新

    for(auto &cache:newClean){
        std::string command="insert into Jotting (J_id,J_content,J_time,N_id) values("+cache.second.first.id()+",""?,?,?)";
    }
}

JottingBroker::JottingBroker()
{

}
