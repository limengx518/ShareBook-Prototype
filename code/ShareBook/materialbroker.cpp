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

        //将从数据库中拿出的数据放在缓存中(旧的净缓存)
        m_oldClean.insert({material->id(),*material});

        return material;
    }
    return material;
}

Material *MaterialBroker::inCache(std::string id)
{
    //判断是否在缓存中
    if(m_oldClean.count(id)){
        return &m_oldClean.at(id);
    }

    if(m_newClean.count(id)){
        return &m_newClean.at(id);
    }

    return nullptr;
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
