#include "materialproxy.h"
#include "materialbroker.h"
#include "material.h"

MaterialProxy::MaterialProxy(const std::string &tid):
    MaterialInterface(tid),_material(nullptr)
{
}

MaterialProxy::~MaterialProxy()
{
    if(_material!=nullptr)
        delete _material;
}


std::string MaterialProxy::getMaterialAbstract()
{
    if(_material==nullptr){
        _material=&(MaterialBroker::getInstance())->findMaterialById(id());
    }
     return _material->getMaterialAbstract();
}
