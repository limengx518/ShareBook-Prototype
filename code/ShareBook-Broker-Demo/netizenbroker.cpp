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
            id=std::to_string(res->getInt(1));
            nickName=res->getString(2);
        }
        //retrieveJotting(id)
        netizen=new Netizen(id,nickName,findJottings(id),findFans(id),findConcereds(id),findComments(id));
        //更新缓存
        update();
        //将从数据库中拿出的数据放在缓存中(旧的净缓存)
        m_oldClean.insert({netizen->id(),*netizen});
        m_oldCleanId.insert(netizen->id());

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
    auto netizen=inCache(m_oldClean,m_oldCleanId,id);
    if(netizen){
        return netizen;
    }

    netizen=inCache(m_newClean,m_newCleanId,id);
    if(netizen){
        return netizen;
    }

    netizen=inCache(m_oldDirty,m_oldDirtyId,id);
    if(netizen){
        return netizen;
    }

    netizen=inCache(m_newDirty,m_newDirtyId,id);
    return netizen;
}

Netizen *NetizenBroker::inCache(std::unordered_map<std::string, Netizen> &cache, std::set<std::string> &cacheId, std::string id)
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

void NetizenBroker::update()
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

void NetizenBroker::updateCache(std::unordered_map<std::string, Netizen> &cache, std::set<std::string> &cacheId,bool isDirty)
{
    //判断缓存大小是否达到最大值，若为最大则删除部分netizen对象
    if(cache.size()==MAX_CAPACITY){
        for(int i=0;i<DELETE_COUNT;i++){
            //获取要删除的netizenId
            auto netizen_id=cacheId.begin();

            //将cache里的netizen存入数据库
            auto netizen=cache.at(*netizen_id);
            std::string command="insert into Netizen (N_id,N_nickName) values("+netizen.id()+","+netizen.nickName()+")";
            RelationalBroker::insert(command);

            //如果是在dirty的缓存中，代表关系改变需要进行联系的修改
            if(isDirty){
                //***删除一个netizen,先判断他是否存在新发布的笔记
                //***若存在，则需将新笔记从new放在old里面
                for(const auto&item:netizen.jottings()){
                    JottingBroker::getInstance()->jottingIsExistInNew(item);
                }
            }

            //将指定netizen以及netizen的id进行删除
            cache.erase(*netizen_id);
            cacheId.erase(netizen_id);
        }
    }
}

void NetizenBroker::cleanToDirtyState(std::string id)
{
    //将netiezn从clean移入dirty
    //并从dirty中删除
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
    for(auto &netizen:m_newDirty){
        std::string command="insert into Netizen (N_id,N_nickName) values("+netizen.second.id()+","+netizen.second.nickName()+")";
        RelationalBroker::insert(command);
    }
    for(auto &netizen:m_oldDirty){
        std::string command="insert into Netizen (N_id,N_nickName) values("+netizen.second.id()+","+netizen.second.nickName()+")";
        RelationalBroker::insert(command);
    }
}

NetizenBroker::NetizenBroker()
{

}
