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
        Jotting *jotting=new Jotting(id,content,time,nid,findMaterial(id),findComment(id));

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

std::vector<std::string> JottingBroker::findComment(std::string jottingId)
{
    std::vector<std::string> commentIds;
std::string com="select M_id from Material where J_id="+jottingId;
    sql::ResultSet* res=RelationalBroker::query(com);
    while (res->next()) {
        commentIds.push_back(std::to_string(res->getInt(1)));
    }
    return commentIds;
}

Jotting* JottingBroker::inCache(std::string objectId)
{
    std::unordered_map<std::string,std::string> m=RelationalBroker::inCache("jotting"+objectId);
    if(m.empty())
        return nullptr;
    std::stringstream materialsId(m["materialId"]);
    std::stringstream commentsId(m["commentId"]);
    std::string id;
    std::vector<std::string> materials,comments;
    while(std::getline(materialsId,id,',')){
        materials.push_back(id);
    }
    while(std::getline(commentsId,id,',')){
        comments.push_back(id);
    }
    Jotting* jotting=new Jotting(objectId,m["note"],m["time"],m["netizenId"],materials,comments);

    return jotting;
}

void JottingBroker::storeObject(const Jotting &jotting)
{
    std::vector<std::string> vector=jotting.materialId();
    std::vector<std::string> comment=jotting.commentId();
    std::string materialsId="";
    std::string commentsId="";
    for(const auto &item:vector){
        materialsId+=item;
        materialsId+=",";
    }
    for(const auto &item:comment){
        commentsId+=item;
        commentsId+=",";
    }
    std::unordered_map<std::string,std::string> map{
        {"note", jotting.note()},
        {"time", jotting.time()},
        {"netizenId", jotting.netizenId()},
        {"materialId",materialsId},
        {"commentId",commentsId}
    };
    RelationalBroker::storeObject("jotting"+jotting.id(),map);
}

JottingBroker::JottingBroker()
{

}
