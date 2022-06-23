#ifndef MATERIALBROKER_H
#define MATERIALBROKER_H

#include "relationalbroker.h"
#include "material.h"
#include <unordered_map>

class MaterialBroker:public RelationalBroker
{
public:
    static MaterialBroker *getInstance();

    Material *findById(std::string id);

    Material* inCache(std::string objectId);
    void storeObject(const Material& material);
    void remove(std::string materialId);

    virtual ~MaterialBroker(){};
private:
    MaterialBroker();
    static MaterialBroker* m_materialBroker;
//    std::unordered_map<std::string, Material> _materialsCache;
};

#endif // MATERIALBROKER_H
