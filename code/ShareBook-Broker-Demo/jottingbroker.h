#ifndef JOTTINGBROKER_H
#define JOTTINGBROKER_H

#include <unordered_map>
#include <jottinginterface.h>
#include <jotting.h>
#include <relationalbroker.h>

class JottingBroker : public RelationalBroker
{
public:
    static JottingBroker *getInstance();
    Jotting &findJottingById(std::string id);
private:
    JottingBroker();
    static JottingBroker* m_jottingBroker;
    std::unordered_map<std::string, Jotting> _jottingsCache;
};

#endif // JOTTINGBROKER_H
