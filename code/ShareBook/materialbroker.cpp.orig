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

        std::string command="select * from Material where J_id="+id;
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

        storeObject(*material);

        return material;
    }
    return material;
}

Material *MaterialBroker::inCache(std::string objectId)
{
    std::unordered_map<std::string,std::string> map=RelationalBroker::inCache("material"+objectId);
    if(map.empty()){
        return nullptr;
    }
    Material* material=new Material(objectId,map["jottingId"],map["path"]);
    return material;
}

void MaterialBroker::storeObject(const Material &material)
{
    std::unordered_map<std::string,std::string> map{
        {"id",material.id()},
        {"path",material.path()},
        {"jottingId",material.jottingId()}
    };
    RelationalBroker::storeObject("material"+material.id(),map);
}


MaterialBroker::MaterialBroker()
{

}
