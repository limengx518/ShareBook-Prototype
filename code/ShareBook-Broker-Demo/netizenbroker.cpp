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
        //更新缓存
        update();
        //将从数据库中拿出的数据放在缓存中(旧的净缓存)
        m_oldClean.insert({netizen->id(),*netizen});
        m_newCleanId.insert(netizen->id());

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

Netizen *NetizenBroker::inCache(std::string id)
{
    if(m_oldClean.find(id)!=m_oldClean.end()){
        //返回netizen的引用
        return &m_oldClean.find(id)->second;
    }

    if(m_newClean.find(id)!=m_newClean.end()){
        //返回netizen的引用
        return &m_newClean.find(id)->second;
    }

    if(m_oldDirty.find(id)!=m_oldDirty.end()){
        //返回netizen的引用
        return &m_oldDirty.find(id)->second;
    }

    if(m_newDirty.find(id)!=m_newDirty.end()){
        //返回netizen的引用
        return &m_newDirty.find(id)->second;
    }

    return nullptr;
}

void NetizenBroker::update()
{
    //判断缓存大小是否达到最大值，若为最大则删除部分netizen对象
    if(m_newClean.size()==MAX_CAPACITY){
        for(int i=0;i<DELETE_COUNT;i++){
            //获取要删除的netizenId
            auto netizen_id=m_newCleanId.begin();

            //将newClean里的material存入数据库
            auto netizen=m_newClean.at(*netizen_id);;
            std::string command="insert into Netizen (N_id,N_nickName) values("+netizen.id()+","+netizen.nickName()+")";
            RelationalBroker::insert(command);

            //将指定material以及material进行删除
            m_newClean.erase(*netizen_id);
            m_newCleanId.erase(netizen_id);
        }
    }

    if(m_oldClean.size()==MAX_CAPACITY){
        for(int i=0;i<DELETE_COUNT;i++){
            auto netizen_id=m_oldCleanId.begin();
            m_oldClean.erase(*netizen_id);
            m_oldCleanId.erase(netizen_id);
        }
    }

    if(m_newDirty.size()==MAX_CAPACITY){
        for(int i=0;i<DELETE_COUNT;i++){
            auto netizen_id=m_newDirtyId.begin();

            //将newDirty里被修改的jotting存入数据库
            auto netizen=m_newDirty.at(*netizen_id);
            std::string command="insert into Netizen (N_id,N_nickName) values("+netizen.id()+","+netizen.nickName()+")";
            RelationalBroker::insert(command);

            m_newDirty.erase(*netizen_id);
            m_newDirtyId.erase(netizen_id);
        }
    }

    if(m_oldDirty.size()==MAX_CAPACITY){
        for(int i=0;i<DELETE_COUNT;i++){
            auto netizen_id=m_oldDirtyId.begin();

            //将oldDirty里被修改的jotting存入数据库
            auto netizen=m_oldDirty.at(*netizen_id);
            std::string command="insert into Netizen (N_id,N_nickName) values("+netizen.id()+","+netizen.nickName()+")";
            RelationalBroker::insert(command);

            m_oldDirty.erase(*netizen_id);
            m_oldDirtyId.erase(netizen_id);
        }
    }
}

void NetizenBroker::addChangeCache(std::string id)
{
    auto netizen=m_newClean.find(id);
    if(netizen!=m_newClean.end()){
        m_newDirty.insert(*netizen);
        m_newDirtyId.insert(netizen->first);
        m_newClean.erase(netizen);
        m_newCleanId.erase(netizen->first);
    }else{
        netizen=m_oldClean.find(id);
        m_oldDirty.insert(*netizen);
        m_oldDirtyId.insert(netizen->first);
        m_oldClean.erase(netizen);
        m_oldCleanId.erase(netizen->first);
    }
}

NetizenBroker::~NetizenBroker()
{
    //程序退出后，将缓存中的新数据存入数据库
    for(auto &netizen:m_newClean){
        std::string command="insert into Netizen (N_id,N_nickName) values("+netizen.second.id()+","+netizen.second.nickName()+")";
        RelationalBroker::insert(command);
    }
}

NetizenBroker::NetizenBroker()
{

}
