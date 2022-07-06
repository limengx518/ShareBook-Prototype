#ifndef MATERIALBROKER_H
#define MATERIALBROKER_H

#include "relationalbroker.h"
#include "material.h"
#include <unordered_map>
#include <set>

class MaterialBroker:public RelationalBroker
{
public:
    static MaterialBroker *getInstance();

    Material *findById(std::string id);

    Material* inCache(std::string id);

    virtual ~MaterialBroker();
private:
    MaterialBroker();
    static MaterialBroker* m_materialBroker;

    std::unordered_map<std::string,Material> m_newClean;

    std::unordered_map<std::string,Material> m_oldClean;
};

#endif // MATERIALBROKER_H
