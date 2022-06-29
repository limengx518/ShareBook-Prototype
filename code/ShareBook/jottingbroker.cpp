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
        Jotting *jotting=new Jotting(id,content,time,nid,findMaterials(id),findComments(id));
        //更新缓存
        update();
        //将从数据库中拿出的数据放在缓存中(旧的净缓存)
        m_oldClean.insert({jotting->id(),*jotting});
        m_oldCleanId.insert(jotting->id());

        std::cout<<"jotting_oldClean:"<<m_oldClean.size()<<"\n";
        std::cout<<"jotting_oldCleanId:"<<m_oldCleanId.size()<<"\n";

        return jotting;
    }

    std::cout<<"in cache"<<std::endl;
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
    auto jotting=inCache(m_oldClean,m_oldCleanId,id);
    if(jotting){
        return jotting;
    }

    jotting=inCache(m_newClean,m_newCleanId,id);
    if(jotting){
        return jotting;
    }

    jotting=inCache(m_oldDirty,m_oldDirtyId,id);
    if(jotting){
        return jotting;
    }

    jotting=inCache(m_newDirty,m_newDirtyId,id);
    return jotting;
}

Jotting *JottingBroker::inCache(std::unordered_map<std::string, Jotting> &cache, std::set<std::string> &cacheId, std::string id)
{
    //根据id判断是否在缓存中
    if(cache.find(id)!=cache.end()){
        //访问量增加，将其Id向“Id队列”的后方移动
        //先删除再插入
        cacheId.erase(id);
        cacheId.insert(id);
        //返回netizen的引用
        return &cache.find(id)->second;
    }
    return nullptr;
}


void JottingBroker::update()
{
    //更新newCleanCache，将其放入数据库后删除缓存中的内容
    updateCache(m_newClean,m_newCleanId,false);

    //更新oldCleanCache，将其删除即可
    if(m_oldClean.size()==MAX_CAPACITY){
        for(int i=0;i<DELETE_COUNT;i++){
            auto netizen_id=m_oldCleanId.begin();
            m_oldClean.erase(*netizen_id);
            m_oldCleanId.erase(netizen_id);
        }
    }

    //更新DirtyCache，将其放入数据库后，不仅要删除缓存中的内容，也要把他与newcaache中jotting的关联删除
    //因为该关联没有被存入数据库中，再次恢复时会出现数据库和缓存不一致的问题
    updateCache(m_newDirty,m_newDirtyId,true);
    updateCache(m_oldDirty,m_oldDirtyId,true);
}

void JottingBroker::updateCache(std::unordered_map<std::string, Jotting> &cache, std::set<std::string> &cacheId, bool isDirty)
{
    //判断缓存大小是否达到最大值，若为最大则删除部分netizen对象
    if(cache.size()==MAX_CAPACITY){
        for(int i=0;i<DELETE_COUNT;i++){
            //获取要删除的jottingId
            auto jotting_id=cacheId.begin();

            //将cache里的netizen存入数据库
            auto jotting=cache.at(*jotting_id);
            std::string command="update Jotting (J_id,J_content,J_time,N_id) values("+jotting.id()+","+jotting.note()+","+jotting.time()+","+jotting.netizenId()+")";
            RelationalBroker::insert(command);

            //如果是在dirty的缓存中，代表关系改变需要进行联系的修改
            if(isDirty){
                //***删除一个jotting,先判断他是否存在新发布的笔记
                //***若存在，则需将新笔记从new放在old里面
                for(const auto&item:jotting.commentId()){
                    CommentBroker::getInstance()->commentIsExistInNew(item);
                }
            }

            //将指定netizen以及netizen的id进行删除
            cache.erase(*jotting_id);
            cacheId.erase(jotting_id);
        }
    }

}

void JottingBroker::cleanToDirtyState(std::string id)
{
    auto jotting=m_newClean.find(id);
    if(jotting!=m_newClean.end()){
        m_newDirty.insert(*jotting);
        m_newDirtyId.insert(jotting->first);
        m_newClean.erase(jotting);
        m_newCleanId.erase(jotting->first);
    }else{
        jotting=m_oldClean.find(id);
        m_oldDirty.insert(*jotting);
        m_oldDirtyId.insert(jotting->first);
        m_oldClean.erase(jotting);
        m_oldCleanId.erase(jotting->first);
    }
}

void JottingBroker::jottingIsExistInNew(std::string id)
{
    auto iterator=m_newCleanId.find(id);
    if(iterator!=m_newCleanId.end()){
        auto jotting= m_newClean.find(id);
        //将在newCleanCache中的jotting存入数据库
        std::string command="insert into Jotting (J_id,J_content,J_time,N_id) values("+jotting->second.id()+","+jotting->second.note()+","+jotting->second.time()+","+jotting->second.netizenId()+")";
        RelationalBroker::insert(command);

        //将jotting放入oldCleanCache中
        m_oldClean.insert(*jotting);
        m_oldCleanId.insert(jotting->first);

        //将jotting从newCleanCache中移除
        m_newClean.erase(id);
        m_newCleanId.erase(iterator);

        return;
    }

    iterator=m_newDirtyId.find(id);
    if(iterator!=m_newDirtyId.end()){
        auto jotting= m_newClean.find(id);
        //将在newDirtyCache中的jotting存入数据库
        std::string command="insert into Jotting (J_id,J_content,J_time,N_id) values("+jotting->second.id()+","+jotting->second.note()+","+jotting->second.time()+","+jotting->second.netizenId()+")";
        RelationalBroker::insert(command);
        //将jotting放入oldCleanCache中
        m_oldClean.insert(*jotting);
        m_oldCleanId.insert(jotting->first);

        m_newDirty.erase(id);
        m_newDirtyId.erase(iterator);
    }

    return;
}

void JottingBroker::addJotting(const Jotting &jotting)
{
    //更新缓存
    update();
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
        std::string command="insert into Jotting (J_id,J_content,J_time,N_id) values("+jotting.second.id()+","+jotting.second.note()+","+jotting.second.time()+","+jotting.second.netizenId()+")";
        RelationalBroker::insert(command);
    }
}

JottingBroker::JottingBroker()
{

}
