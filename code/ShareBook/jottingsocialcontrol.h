#ifndef JOTTINGSOCIALCONTROL_H
#define JOTTINGSOCIALCONTROL_H

#include "netizen.h"
#include <unordered_map>
#include "jotting.h"
#include <nlohmann/json.hpp>

class Material;

class JottingSocialControl
{
public:
    static JottingSocialControl *getInstance();
    ~JottingSocialControl();
    nlohmann::json login(std::string netizenId);
    nlohmann::json pushJottings(std::string netizenId);
    nlohmann::json checkOneJotting(std::string netizenId,std::string jottingId);
    bool comment(std::string netizenId, std::string jottingId, std::string content);
private:
    explicit JottingSocialControl();
    static JottingSocialControl * m_jottingSocialControl;
};

#endif // JOTTINGSOCIALCONTROL_H
