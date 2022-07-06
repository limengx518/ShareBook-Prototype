#ifndef NETIZENBROKER_H
#define NETIZENBROKER_H

#include "relationalbroker.h"
#include "netizen.h"
#include <set>

class NetizenBroker:public RelationalBroker
{
public:
    static NetizenBroker* getInstance();

    Netizen *findById(std::string id);
    std::vector<std::string> findJottings(std::string netizenId);
    std::vector<std::string> findFans(std::string netizenId);
    std::vector<std::string> findConcereds(std::string netizenId);
    std::vector<std::string> findComments(std::string netizenId);

    void cleanToDirtyState(std::string id);   //更新的操作时改变缓存

    virtual ~NetizenBroker();
private:
    NetizenBroker();

    static NetizenBroker *m_netizenBroker;

    std::unordered_map<std::string,Netizen> m_newClean;

    std::unordered_map<std::string,Netizen> m_oldClean;

    std::unordered_map<std::string,Netizen> m_newDirty;

    std::unordered_map<std::string,Netizen> m_oldDirty;

    Netizen *inCache(std::string id);
    void threadRefresh();
    void refresh(const boost::system::error_code &error_code,boost::asio::deadline_timer* timer);
};

#endif // NETIZENBROKER_H
