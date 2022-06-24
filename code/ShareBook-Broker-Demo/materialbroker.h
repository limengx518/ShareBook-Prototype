#ifndef MATERIALBROKER_H
#define MATERIALBROKER_H

#include "relationalbroker.h"
#include "material.h"
#include <unordered_map>
#include <set>

#define MAX_CAPACITY 30
#define DELETE_COUNT 15

class MaterialBroker:public RelationalBroker
{
public:
    static MaterialBroker *getInstance();

    Material *findById(std::string id);

    Material* inCache(std::string id);

    void update() override;

    virtual ~MaterialBroker();
private:
    MaterialBroker();
    static MaterialBroker* m_materialBroker;

    std::unordered_map<std::string,Material> m_newClean;
    std::set<std::string> m_newCleanId;

    std::unordered_map<std::string,Material> m_oldClean;
    std::set<std::string> m_oldCleanId;
};

#endif // MATERIALBROKER_H
