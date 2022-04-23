#ifndef JOTTINGBROKER_H
#define JOTTINGBROKER_H

#include "broker.h"
#include <vector>

class Jotting;
class Netizen;

class JottingBroker : public Broker
{
public:
    JottingBroker();
    std::vector<Jotting> find_Netizen_Jottings(int netizenId);
    std::vector<Jotting> findSomeJottings();
    void setJottings(std::vector<Jotting> jottings);
    std::vector<Jotting> getJottings();
private:
    std::vector<Jotting> m_jottings;
};

#endif // JOTTINGBROKER_H
