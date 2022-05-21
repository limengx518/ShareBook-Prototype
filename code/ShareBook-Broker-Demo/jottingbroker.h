#ifndef JOTTINGBROKER_H
#define JOTTINGBROKER_H

#include <unordered_map>
#include <jottinginterface.h>
#include <jotting.h>
#include <relationalbroker.h>
#include <vector>

class JottingBroker : public RelationalBroker
{
public:
    static JottingBroker *getInstance();
    Jotting *findById(std::string id);
    std::vector<std::string> getSomeJottingsId(std::string lastTime,std::string thisTime);
    void addNewJotting(Jotting * jotting);
    virtual ~JottingBroker(){}
    std::vector<std::string> findMaterial(std::string jottingId);
private:
    JottingBroker();
    static JottingBroker* m_jottingBroker;
    std::unordered_map<std::string, Jotting> _jottingsCache;
};

#endif // JOTTINGBROKER_H
