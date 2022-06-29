#include "materialbroker.h"
#include <unordered_map>

MaterialBroker* MaterialBroker::m_materialBroker=NULL;

MaterialBroker *MaterialBroker::getInstance()
{
    if(m_materialBroker==nullptr){
        m_materialBroker=new MaterialBroker();
    }
    return m_materialBroker;
}

Material *MaterialBroker::findById(std::string id)
{
    Material* material=inCache(id);
    if(material==nullptr){

        std::string command="select * from Material where M_id="+id;
        sql::ResultSet* res=RelationalBroker::query(command);
        std::string id,path,jId;
            // Loop through and print results
        while (res->next()) {
            id=std::to_string(res->getInt(1));
            path=res->getString(2);
            jId=std::to_string(res->getInt(3));
        }
        //retrieveJotting(id)
        Material* material=new Material(id,jId,path);

        //更新缓存
        update();
        //将从数据库中拿出的数据放在缓存中(旧的净缓存)
        m_oldClean.insert({material->id(),*material});
        m_oldCleanId.insert(material->id());

        return material;
    }
    return material;
}

Material *MaterialBroker::inCache(std::string id)
{
    //判断是否在缓存中
    auto material=inCache(m_oldClean,m_oldCleanId,id);
    if(material){
        return material;
    }

    material=inCache(m_newClean,m_newCleanId,id);
    if(material){
        return material;
    }

    return material;
}

Material *MaterialBroker::inCache(std::unordered_map<std::string, Material> &cache, std::set<std::string> &cacheId, std::string id)
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

void MaterialBroker::update()
{
    //判断缓存大小是否达到最大值，若为最大则删除部分material对象
    if(m_newClean.size()==MAX_CAPACITY){
        for(int i=0;i<DELETE_COUNT;i++){
            //获取要删除的materialId
            auto material_id=m_newCleanId.begin();

            //将newClean里的material存入数据库
            auto material=m_newClean.at(*material_id);
            std::string command="insert into Material (M_id,M_path,J_id) values("+material.id()+","+material.path()+","+material.jottingId()+")";
            RelationalBroker::insert(command);

            //将指定material以及material进行删除
            m_newClean.erase(*material_id);
            m_newCleanId.erase(material_id);
        }
    }

    if(m_oldClean.size()==MAX_CAPACITY){
        for(int i=0;i<DELETE_COUNT;i++){
            auto material_id=m_oldCleanId.begin();
            m_oldClean.erase(*material_id);
            m_oldCleanId.erase(material_id);
        }
    }
}

MaterialBroker::~MaterialBroker()
{
    //程序退出后，将缓存中的新数据存入数据库
    for(auto &material:m_newClean){
        std::string command="insert into Material (M_id,M_path,J_id) values("+material.second.id()+","+material.second.path()+","+material.second.jottingId()+")";
        RelationalBroker::insert(command);
    }
}

MaterialBroker::MaterialBroker()
{

}
