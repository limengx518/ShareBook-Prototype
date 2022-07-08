

#include "netizenbroker.h"
#include "jottingbroker.h"

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
            id=std::to_string(res->getUInt(1));
            nickName=res->getString(2);
        }
        //retrieveJotting(id)
        netizen=new Netizen(id,nickName,findJottings(id),findFans(id),findConcereds(id),findComments(id));
        //将从数据库中拿出的数据放在缓存中(旧的净缓存)
        m_oldClean.insert({netizen->id(),*netizen});
    }
    return netizen;
}


std::vector<std::string> NetizenBroker::findJottings(std::string netizenId)
{
    std::string com="select J_id from Jotting where N_id="+netizenId;
    sql::ResultSet* res=RelationalBroker::query(com);
    std::vector<std::string> jottingIds;
    while (res->next()) {
        jottingIds.push_back(std::to_string(res->getUInt(1)));
    }
    return jottingIds;

}

std::vector<std::string> NetizenBroker::findFans(std::string netizenId)
{
    std::string com="select N_Fan_id from Relation where N_id="+netizenId;
    std::vector<std::string> fansIds;
     sql::ResultSet* res=RelationalBroker::query(com);
     while (res->next()) {
         fansIds.push_back(std::to_string(res->getUInt(1)));
     }
    return fansIds;
}

std::vector<std::string> NetizenBroker::findConcereds(std::string netizenId)
{
    std::string com="select N_id from Relation where N_Fan_id="+netizenId;
    std::vector<std::string> conceredIds;
     sql::ResultSet* res=RelationalBroker::query(com);

     while (res->next()) {
         conceredIds.push_back(std::to_string(res->getUInt(1)));
     }
    return conceredIds;

}

std::vector<std::string> NetizenBroker::findComments(std::string netizenId)
{
    std::string com="select C_id from Comment where J_id="+netizenId;
    std::vector<std::string> commentIds;
    sql::ResultSet* res=RelationalBroker::query(com);

     while (res->next()) {
         commentIds.push_back(std::to_string(res->getUInt(1)));
     }
     return commentIds;
}

Netizen *NetizenBroker::inCache(std::string id)
{
    //判断是否在缓存中
    if(m_oldClean.count(id)){
        return &m_oldClean.at(id);
    }

    if(m_newClean.count(id)){
        return &m_newClean.at(id);
    }

    if(m_oldDirty.count(id)){
        return &m_oldDirty.at(id);
    }

    if(m_newDirty.count(id)){
        return &m_newDirty.at(id);
    }

    return nullptr;
}

void NetizenBroker::cleanToDirtyState(std::string id)
{
    //将netiezn从clean移入dirty
    //并从dirty中删除
    auto netizen=m_newClean.find(id);
    if(netizen!=m_newClean.end()){
        m_newDirty.insert(*netizen);
        m_newClean.erase(netizen);
    }else{
        netizen=m_oldClean.find(id);
        m_oldDirty.insert(*netizen);
        m_oldClean.erase(netizen);
    }
}


NetizenBroker::~NetizenBroker()
{
    //程序退出后，将缓存中的新数据存入数据库
    for(auto &netizen:m_newClean){
        std::string command="insert into Netizen (N_id,N_nickName) values("+netizen.second.id()+","+netizen.second.nickName()+")";
        RelationalBroker::insert(command);
    }
    for(auto &netizen:m_newDirty){
        std::string command="insert into Netizen (N_id,N_nickName) values("+netizen.second.id()+","+netizen.second.nickName()+")";
        RelationalBroker::insert(command);
    }
    for(auto &netizen:m_oldDirty){
        std::string command="insert into Netizen (N_id,N_nickName) values("+netizen.second.id()+","+netizen.second.nickName()+")";
        RelationalBroker::insert(command);
    }
}

void NetizenBroker::threadRefresh()
{
    boost::asio::io_service io_service;
    boost::asio::deadline_timer timer(io_service,boost::posix_time::seconds(30));
    timer.async_wait(boost::bind(&NetizenBroker::refresh,this,boost::asio::placeholders::error(),&timer));
    io_service.run();
}

void NetizenBroker::refresh(const boost::system::error_code &error_code,boost::asio::deadline_timer* timer)
{
    std::lock_guard<std::mutex> lk(m_mutex);
    std::string command="insert into Jotting (J_id,J_content,J_time,N_id) values(6,'hello world','2022-07-06 10:05:01',1)";
    RelationalBroker::insert(command);
    timer->expires_at(timer->expires_at() + boost::posix_time::seconds(30));
    timer->async_wait(boost::bind(&NetizenBroker::refresh,this,boost::asio::placeholders::error,timer));
}

NetizenBroker::NetizenBroker()
{
//    std::thread t(&NetizenBroker::threadRefresh,this);
//    t.join();
}
