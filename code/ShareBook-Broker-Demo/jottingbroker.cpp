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
        //更新缓存
        update();
        //将从数据库中拿出的数据放在缓存中(旧的净缓存)
        m_oldClean.insert({jotting->id(),*jotting});
        m_newCleanId.insert(jotting->id());

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
    if(m_oldClean.find(id)!=m_oldClean.end()){
        //返回jotting的引用
        return &m_oldClean.find(id)->second;
    }

    if(m_newClean.find(id)!=m_newClean.end()){
        //返回jotting的引用
        return &m_newClean.find(id)->second;
    }

    return nullptr;
}

void JottingBroker::update()
{
    //判断缓存大小是否达到最大值，若为最大则删除部分jotting对象
    if(m_newClean.size()==MAX_CAPACITY){
        std::cout<<"删除相关内容\n";
        for(int i=0;i<DELETE_COUNT;i++){
            //获取要删除的jottingId
            auto jotting_id=m_newCleanId.begin();

            //将newClean里的jotting存入数据库
            auto jotting=m_newClean.at(*jotting_id);
            std::string command="insert into Jotting (J_id,J_content,J_time,N_id) values("+jotting.id()+","+jotting.note()+","+jotting.time()+","+jotting.netizenId()+")";
            RelationalBroker::insert(command);

            //将指定jotting以及jottingid进行删除
            m_newClean.erase(*jotting_id);
            m_newCleanId.erase(jotting_id);
        }
    }

    if(m_oldClean.size()==MAX_CAPACITY){
        for(int i=0;i<DELETE_COUNT;i++){
            auto jotting_id=m_oldCleanId.begin();
            m_oldClean.erase(*jotting_id);
            m_oldCleanId.erase(jotting_id);
        }
    }

}

JottingBroker::~JottingBroker()
{
    //程序退出后，将缓存中的新数据存入数据库
    for(auto &jotting:m_newClean){
        std::string command="insert into Jotting (J_id,J_content,J_time,N_id) values("+jotting.second.id()+","+jotting.second.note()+","+jotting.second.time()+","+jotting.second.netizenId()+")";
        RelationalBroker::insert(command);
    }
}

JottingBroker::JottingBroker()
{

}
