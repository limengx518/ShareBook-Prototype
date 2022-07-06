#include "jottingbroker.h"
#include <unordered_map>
#include <sstream>
#include <string>
#include <vector>
#include "commentbroker.h"

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
        jotting=new Jotting(id,content,time,nid,findMaterials(id),findComments(id));

        //将从数据库中拿出的数据放在缓存中(旧的净缓存)
        m_oldClean.insert({jotting->id(),*jotting});
    }

    return jotting;
}

std::vector<JottingProxy> JottingBroker::pushJottings(std::string netizenId, std::string lastTime, std::string thisTime)
{
    std::cout<<"lastTime:"<<lastTime<<std::endl;
    std::cout<<"thisTime:"<<thisTime<<std::endl;
    thisTime="2022-09-25 21:27:59";
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

void JottingBroker::threadRefresh()
{
    boost::asio::io_service io_service;
    boost::asio::deadline_timer timer(io_service,boost::posix_time::seconds(30));
    timer.async_wait(boost::bind(&JottingBroker::refresh,this,boost::asio::placeholders::error(),&timer));
    io_service.run();
}

void JottingBroker::refresh(const boost::system::error_code &error_code,boost::asio::deadline_timer* timer)
{
//    for(auto &jotting:m_newClean){
//        std::lock_guard<std::mutex> lk(m_mutex);
//        std::string command="insert into Jotting (J_id,J_content,J_time,N_id) values("+jotting.second.id()+","+jotting.second.note()+","+jotting.second.time()+","+jotting.second.netizenId()+")";
//        RelationalBroker::insert(command);
//    }
//    for(auto &jotting:m_newDirty){
//        std::lock_guard<std::mutex> lk(m_mutex);
//        std::string command="insert into Jotting (J_id,J_content,J_time,N_id) values("+jotting.second.id()+","+jotting.second.note()+","+jotting.second.time()+","+jotting.second.netizenId()+")";
//        RelationalBroker::insert(command);
//    }
//    for(auto &jotting:m_oldDirty){
//        std::lock_guard<std::mutex> lk(m_mutex);
//        std::string command="update Jotting (J_id,J_content,J_time,N_id) values("+jotting.second.id()+","+jotting.second.note()+","+jotting.second.time()+","+jotting.second.netizenId()+")";
//        RelationalBroker::insert(command);
//    }
    std::lock_guard<std::mutex> lk(m_mutex);
    std::string command="insert into Jotting (J_id,J_content,J_time,N_id) values(6,'hello world','2022-07-06 10:05:01',1)";
    RelationalBroker::insert(command);
    timer->expires_at(timer->expires_at() + boost::posix_time::seconds(30));
    timer->async_wait(boost::bind(&JottingBroker::refresh,this,boost::asio::placeholders::error,timer));
}

void JottingBroker::cleanToDirtyState(std::string id)
{
    auto jotting=m_newClean.find(id);
    if(jotting!=m_newClean.end()){
        m_newDirty.insert(*jotting);
        m_newClean.erase(jotting);
    }else{
        jotting=m_oldClean.find(id);
        m_oldDirty.insert(*jotting);
        m_oldClean.erase(jotting);
    }
}

void JottingBroker::addJotting(const Jotting &jotting)
{
    //将从数据库中拿出的数据放在缓存中(旧的净缓存)
    m_newClean.insert({jotting.id(),jotting});
}

JottingBroker::~JottingBroker()
{
    //程序退出后，将缓存中的新数据存入数据库
    for(auto &jotting:m_newClean){
        std::string command="insert into Jotting (J_id,J_content,J_time,N_id) values("+jotting.second.id()+","+jotting.second.note()+","+jotting.second.time()+","+jotting.second.netizenId()+")";
        RelationalBroker::insert(command);
    }
    for(auto &jotting:m_newDirty){
        std::string command="insert into Jotting (J_id,J_content,J_time,N_id) values("+jotting.second.id()+","+jotting.second.note()+","+jotting.second.time()+","+jotting.second.netizenId()+")";
        RelationalBroker::insert(command);
    }
    for(auto &jotting:m_oldDirty){
        std::string command="update Jotting (J_id,J_content,J_time,N_id) values("+jotting.second.id()+","+jotting.second.note()+","+jotting.second.time()+","+jotting.second.netizenId()+")";
        RelationalBroker::insert(command);
    }
}

JottingBroker::JottingBroker()
{
    std::thread t(&JottingBroker::threadRefresh,this);
    t.join();
}
