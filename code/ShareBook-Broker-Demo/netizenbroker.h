#ifndef NETIZENBROKER_H
#define NETIZENBROKER_H

#include "relationalbroker.h"
#include "netizen.h"

class NetizenBroker:public RelationalBroker
{
public:
    static NetizenBroker* getInstance();

    Netizen *findById(std::string id);
    std::vector<std::string> findJottings(std::string netizenId);
    std::vector<std::string> findFans(std::string netizenId);
    std::vector<std::string> findConcereds(std::string netizenId);
    std::vector<std::string> findComments(std::string netizenId);

    Netizen *inCache(std::string objectId);
    void storeObject(const Netizen& netizen);
    void remove(const std::string netizenId);

    virtual ~NetizenBroker(){};
private:
    NetizenBroker();

    static NetizenBroker *m_netizenBroker;
};

#endif // NETIZENBROKER_H
