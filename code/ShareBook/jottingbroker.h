#ifndef JOTTINGBROKER_H
#define JOTTINGBROKER_H

#include <unordered_map>
#include <set>
#include <jottinginterface.h>
#include <jotting.h>
#include "relationalbroker.h"
#include <vector>
#include "jottingproxy.h"
#include <mutex>

class JottingBroker : public RelationalBroker
{
public:
    static JottingBroker *getInstance();

    Jotting *findById(std::string id);
    std::vector<JottingProxy> pushJottings(std::string netizenId,std::string lastTime,std::string thisTime);
    std::vector<std::string> findMaterials(std::string jottingid);
    std::vector<std::string> findComments(std::string jottingId);

    void cleanToDirtyState(std::string id);   //更新的操作时改变缓存

    void addJotting(const Jotting& jotting);

    virtual ~JottingBroker();
private:
    JottingBroker();
    static JottingBroker* m_jottingBroker;
    std::mutex m_mutex;

    std::unordered_map<std::string,Jotting> m_newClean;
    std::unordered_map<std::string,Jotting> m_oldClean;
    std::unordered_map<std::string,Jotting> m_newDirty;
    std::unordered_map<std::string,Jotting> m_oldDirty;

    Jotting* inCache(std::string id);
    void threadRefresh();
    void refresh(const boost::system::error_code &error_code,boost::asio::deadline_timer* timer);
};

#endif // JOTTINGBROKER_H
