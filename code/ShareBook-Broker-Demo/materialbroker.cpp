#include "materialbroker.h"

MaterialBroker* MaterialBroker::m_materialBroker=NULL;

MaterialBroker *MaterialBroker::getInstance()
{
    if(m_materialBroker==nullptr){
        m_materialBroker=new MaterialBroker();
    }
    return m_materialBroker;
}

Material &MaterialBroker::findMaterialById(std::string id)
{
    auto search = _materialsCache.find(id);
    if(search == _materialsCache.end()){
        //retrieveJotting(id)
        Material material=*(RelationalBroker::findMaterialById(id));
        _materialsCache.insert(std::pair<std::string,Material>(id,material));
    }
     return _materialsCache.at(id);

}

MaterialBroker::MaterialBroker()
{

}
