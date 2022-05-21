#include "materialbroker.h"

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
    auto search = _materialsCache.find(id);
    if(search == _materialsCache.end()){
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
        _materialsCache.insert(std::pair<std::string,Material>(id,*material));
    }
     return &_materialsCache.at(id);
}

void MaterialBroker::addNewMaterial(Material *material)
{
    _materialsCache.insert(std::pair<std::string,Material>(material->id(),*material));
}

MaterialBroker::MaterialBroker()
{

}
