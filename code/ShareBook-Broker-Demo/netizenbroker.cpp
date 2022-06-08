#include "netizenbroker.h"

NetizenBroker* NetizenBroker::m_netizenBroker=NULL;

NetizenBroker *NetizenBroker::getInstance()
{
    if(m_netizenBroker==nullptr){
        m_netizenBroker=new NetizenBroker();
    }
    return m_netizenBroker;
}

Netizen *NetizenBroker::findById(std::string id)
{
    Netizen * netizen=inCache(id);
    if(netizen==nullptr){
        std::string com="select * from Netizen where N_id="+id;
        std::string id,nickName;
        sql::ResultSet* res=RelationalBroker::query(com);
        // Loop through and print results
        while (res->next()) {
            id=std::to_string(res->getInt(1));
            nickName=res->getString(2);
        }
        //retrieveJotting(id)
        Netizen* netizen=new Netizen(id,nickName,findJottings(id),findFans(id),findConcereds(id),findComments(id));

        storeObject(*netizen);

        return netizen;
    }
    return netizen;
}


std::vector<std::string> NetizenBroker::findJottings(std::string netizenId)
{
    std::string com="select J_id from Jotting where N_id="+netizenId;
    sql::ResultSet* res=RelationalBroker::query(com);
    std::vector<std::string> jottingIds;
    while (res->next()) {
        jottingIds.push_back(std::to_string(res->getInt(1)));
    }
    return jottingIds;

}

std::vector<std::string> NetizenBroker::findFans(std::string netizenId)
{
    std::string com="select N_Fan_id from Relation where R_id="+netizenId;
    std::vector<std::string> fansIds;
     sql::ResultSet* res=RelationalBroker::query(com);
     while (res->next()) {
         fansIds.push_back(std::to_string(res->getInt(1)));
     }
    return fansIds;
}

std::vector<std::string> NetizenBroker::findConcereds(std::string netizenId)
{
    std::string com="select R_id from Relation where N_Fan_id="+netizenId;
    std::vector<std::string> conceredIds;
     sql::ResultSet* res=RelationalBroker::query(com);

     while (res->next()) {
         conceredIds.push_back(std::to_string(res->getInt(1)));
     }
    return conceredIds;

}

std::vector<std::string> NetizenBroker::findComments(std::string netizenId)
{
    std::string com="select C_id from Comment where J_id="+netizenId;
    std::vector<std::string> commentIds;
    sql::ResultSet* res=RelationalBroker::query(com);

     while (res->next()) {
         commentIds.push_back(std::to_string(res->getInt(1)));
     }
    return commentIds;
}

Netizen *NetizenBroker::inCache(std::string objectId)
{
    std::unordered_map<std::string,std::string> map=RelationalBroker::inCache("netizen"+objectId);
    if(map.empty())
        return nullptr;
    std::stringstream jottingsId(map["jottingsId"]);
    std::stringstream concernedsId(map["concernedsId"]);
    std::stringstream fansId(map["fansId"]);
    std::stringstream commentsId(map["commentsId"]);
    std::string id;
    std::vector<std::string> jottings;
    while(std::getline(jottingsId,id,',')){
        jottings.push_back(id);
    }
    std::vector<std::string> concerneds;
    while(std::getline(concernedsId,id,',')){
        concerneds.push_back(id);
    }
    std::vector<std::string> fans;
    while(std::getline(fansId,id,',')){
        fans.push_back(id);
    }
    std::vector<std::string> comments;
    while(std::getline(commentsId,id,',')){
        comments.push_back(id);
    }
    Netizen * netizen=new Netizen(objectId,map["nickName"],jottings,fans,concerneds,comments);
    return netizen;
}

void NetizenBroker::storeObject(const Netizen &netizen)
{
    std::vector<std::string> jottings=netizen.jottings();
    std::vector<std::string> fans=netizen.fans();
    std::vector<std::string> concerneds=netizen.concerneds();
    std::string jottingsId,fansId,concernedsId,commentsId;
    for(const auto& item:jottings){
        jottingsId+=item;
        jottingsId+=",";
    }
    for(const auto& item:fans){
        fansId+=item;
        fansId+=",";
    }
    for(const auto& item:concerneds){
        concernedsId+=item;
        concernedsId+=",";
    }
    for(const auto& item:concerneds){
        commentsId+=item;
        commentsId=",";
    }
    std::unordered_map<std::string,std::string> map{
        {"id",netizen.id()},
        {"nickName",netizen.nickName()},
        {"jottingsId",jottingsId},
        {"fansId",fansId},
        {"concernedsId",concernedsId},
        {"commentsId",commentsId}
    };

    RelationalBroker::storeObject("netizen"+netizen.id(),map);
}

void NetizenBroker::remove(const std::string netizenId)
{
    RelationalBroker::remove("netizen"+netizenId);
}

NetizenBroker::NetizenBroker()
{

}
