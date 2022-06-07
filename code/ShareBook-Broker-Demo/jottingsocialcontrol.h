#ifndef JOTTINGSOCIALCONTROL_H
#define JOTTINGSOCIALCONTROL_H

#include "netizen.h"
#include <unordered_map>
#include "jotting.h"

class Material;

class JottingSocialControl
{
public:
    explicit JottingSocialControl();
    ~JottingSocialControl();
    void login(std::string netizenId);
    void pushJottings(std::string lastTime,std::string thisTime);
    void checkOneJotting(std::string objectId);
    void addComment(std::string netizenId, std::string jottingId, std::string content);
};

#endif // JOTTINGSOCIALCONTROL_H
