#ifndef NETIZENBROKER_H
#define NETIZENBROKER_H

#include "relationalbroker.h"
#include "netizen.h"
#include <set>

#define MAX_CAPACITY 30
#define DELETE_COUNT 15

class NetizenBroker:public RelationalBroker
{
public:
    static NetizenBroker* getInstance();

    Netizen *findById(std::string id);
    std::vector<std::string> findJottings(std::string netizenId);
    std::vector<std::string> findFans(std::string netizenId);
    std::vector<std::string> findConcereds(std::string netizenId);
    std::vector<std::string> findComments(std::string netizenId);

    Netizen *inCache(std::string id);

    void update() override;

    void addChangeCache(std::string id);   //更新的操作时改变缓存

    virtual ~NetizenBroker();
private:
    NetizenBroker();

    static NetizenBroker *m_netizenBroker;

    std::unordered_map<std::string,Netizen> m_newClean;
    std::set<std::string> m_newCleanId;

    std::unordered_map<std::string,Netizen> m_oldClean;
    std::set<std::string> m_oldCleanId;

    std::unordered_map<std::string,Netizen> m_newDirty;
    std::set<std::string> m_newDirtyId;

    std::unordered_map<std::string,Netizen> m_oldDirty;
    std::set<std::string> m_oldDirtyId;
};

#endif // NETIZENBROKER_H
