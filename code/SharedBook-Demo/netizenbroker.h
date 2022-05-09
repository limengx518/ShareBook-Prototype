#ifndef NETIZENBROKER_H
#define NETIZENBROKER_H

#include "broker.h"
#include <vector>

class Netizen;
class NetizenBroker : public Broker
{
public:
    NetizenBroker();
    Netizen* findNetizenByID(int netizenId);
    std::vector<Netizen> findFansByID(int netizenId);
    std::vector<Netizen> findInterestsByID(int netizenId);

    void setNetizens(std::vector<Netizen> netizens);
private:
    std::vector<Netizen> m_netizens;
};

#endif // NETIZENBROKER_H
