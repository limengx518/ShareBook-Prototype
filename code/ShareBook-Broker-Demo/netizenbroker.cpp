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
    auto search = _netizensCache.find(id);
    if(search == _netizensCache.end()){
            std::string com="select * from Netizen where N_id="+id;
            std::string id,nickName;
            sql::ResultSet* res=RelationalBroker::query(com);
                // Loop through and print results
            while (res->next()) {
                id=std::to_string(res->getInt(1));
                nickName=res->getString(2);
            }
        //retrieveJotting(id)
        Netizen* netizen=new Netizen(id,nickName,findNetizenJotting(id),findNetizenFans(id),findNetizenConcereds(id));
        _netizensCache.insert(std::pair<std::string,Netizen>(id,*netizen));
    }
    return &_netizensCache.at(id);
}

NetizenBroker::~NetizenBroker()
{
    if(m_netizenBroker!=nullptr)
        delete m_netizenBroker;
}

std::vector<std::string> NetizenBroker::findNetizenJotting(std::string netizenId)
{
    std::string com="select J_id from Jotting where N_id="+netizenId;
    sql::ResultSet* res=RelationalBroker::query(com);
    std::vector<std::string> jottingIds;
    while (res->next()) {
        jottingIds.push_back(std::to_string(res->getInt(1)));
    }
    return jottingIds;

}

std::vector<std::string> NetizenBroker::findNetizenFans(std::string netizenId)
{
    std::string com="select N_Fan_id from Relation where R_id="+netizenId;
    std::vector<std::string> fansIds;
     sql::ResultSet* res=RelationalBroker::query(com);
     while (res->next()) {
         fansIds.push_back(std::to_string(res->getInt(1)));
     }
    return fansIds;
}

std::vector<std::string> NetizenBroker::findNetizenConcereds(std::string netizenId)
{
    std::string com="select R_id from Relation where N_Fan_id="+netizenId;
    std::vector<std::string> conceredIds;
     sql::ResultSet* res=RelationalBroker::query(com);

     while (res->next()) {
         conceredIds.push_back(std::to_string(res->getInt(1)));
     }
    return conceredIds;

}

NetizenBroker::NetizenBroker()
{

}
