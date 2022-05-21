#ifndef NETIZENBROKER_H
#define NETIZENBROKER_H

#include "relationalbroker.h"
#include "netizen.h"

class NetizenBroker:public RelationalBroker
{
public:
    static NetizenBroker* getInstance();
    Netizen *findById(std::string id);
    virtual ~NetizenBroker();

    std::vector<std::string> findNetizenJotting(std::string netizenId);
    std::vector<std::string> findNetizenFans(std::string netizenId);
    std::vector<std::string> findNetizenConcereds(std::string netizenId);
private:
    NetizenBroker();

    static NetizenBroker *m_netizenBroker;
    std::unordered_map<std::string, Netizen> _netizensCache;
};

#endif // NETIZENBROKER_H
