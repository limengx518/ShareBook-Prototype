#ifndef JOTTINGBROKER_H
#define JOTTINGBROKER_H

#include <unordered_map>
#include <jottinginterface.h>
#include <jotting.h>
#include "relationalbroker.h"
#include <vector>
#include "jottingproxy.h"

class JottingBroker : public RelationalBroker
{
public:
    static JottingBroker *getInstance();

    Jotting *findById(std::string id);
    std::vector<JottingProxy> pushJottings(std::string netizenId,std::string lastTime,std::string thisTime);
    std::vector<std::string> findMaterials(std::string jottingid);
    std::vector<std::string> findComments(std::string jottingId);

    Jotting* inCache(std::string id);

    void update() override;

    virtual ~JottingBroker(){};
private:
    JottingBroker();
    static JottingBroker* m_jottingBroker;

    std::unordered_map<std::string,std::pair<Jotting,int>> newClean;
//    std::unordered_map<std::string,std::pair<Jotting,int>> newDirty;

    std::unordered_map<std::string,std::pair<Jotting,int>> oldClean;
//    std::unordered_map<std::string,std::pair<Jotting,int>> oldDirty;
};

#endif // JOTTINGBROKER_H
