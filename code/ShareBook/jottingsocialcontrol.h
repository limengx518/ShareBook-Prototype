#ifndef JOTTINGSOCIALCONTROL_H
#define JOTTINGSOCIALCONTROL_H

#include "netizen.h"
#include <unordered_map>
#include "jotting.h"
#include <nlohmann/json.hpp>
#include "mytimer.h"

class Material;

class JottingSocialControl
{
public:
    explicit JottingSocialControl();
    ~JottingSocialControl();
    nlohmann::json login(std::string netizenId);
    nlohmann::json pushJottings(std::string netizenId);
    nlohmann::json checkOneJotting(std::string netizenId,std::string jottingId);
    bool comment(std::string netizenId, std::string jottingId, std::string content);
    bool publishJotting(std::string netizenId, nlohmann::json jottingContent);
    void follow(std::string nId,std::string concernedId);
    nlohmann::json scanMessage(std::string netizenId);
    nlohmann::json checkMessage(std::string netizenId,std::string messageId);

private:
    static void flush();
    static void NotificationFlush();
    MyTimer m_timer;
    MyTimer m_NotificationTimer;
};

#endif // JOTTINGSOCIALCONTROL_H
