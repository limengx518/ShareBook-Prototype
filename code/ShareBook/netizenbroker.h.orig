#ifndef NETIZENBROKER_H
#define NETIZENBROKER_H

#include "relationalbroker.h"
#include "netizen.h"

class NetizenBroker:public RelationalBroker
{
public:
    static NetizenBroker* getInstance();

    Netizen *findById(std::string id);
    std::vector<std::string> findNetizenJotting(std::string netizenId);
    std::vector<std::string> findNetizenFans(std::string netizenId);
    std::vector<std::string> findNetizenConcereds(std::string netizenId);

    Netizen *inCache(std::string objectId);
    void storeObject(const Netizen& netizen);
    virtual ~NetizenBroker(){};
private:
    NetizenBroker();

    static NetizenBroker *m_netizenBroker;
};

#endif // NETIZENBROKER_H
