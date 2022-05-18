#ifndef NETIZENBROKER_H
#define NETIZENBROKER_H

#include "relationalbroker.h"
#include "netizen.h"

class NetizenBroker:public RelationalBroker
{
public:
    static NetizenBroker* getInstance();
    Netizen &findNetizenById(std::string id);
    ~NetizenBroker();
private:
    NetizenBroker();

    static NetizenBroker *m_netizenBroker;
    std::unordered_map<std::string, Netizen> _netizensCache;
};

#endif // NETIZENBROKER_H
