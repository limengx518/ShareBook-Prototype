#ifndef JOTTINGBROKER_H
#define JOTTINGBROKER_H

#include <unordered_map>
#include <jottinginterface.h>
#include <jotting.h>
#include <relationalbroker.h>
#include <vector>
#include "cache.h"

class JottingBroker : public RelationalBroker
{
public:
    static JottingBroker *getInstance();

    Jotting *findById(std::string id);
    std::vector<std::string> getSomeJottingsId(std::string lastTime,std::string thisTime);
    std::vector<std::string> findMaterials(std::string jottingid);
    std::vector<std::string> findComments(std::string jottingId);

    Jotting* inCache(std::string objectId);
    void storeObject(const Jotting& jotting);

    virtual ~JottingBroker(){};
private:
    JottingBroker();
    static JottingBroker* m_jottingBroker;
};

#endif // JOTTINGBROKER_H
