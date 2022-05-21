#ifndef JOTTINGSOCIALCONTROL_H
#define JOTTINGSOCIALCONTROL_H

#include "netizen.h"
#include <unordered_map>
#include "jotting.h"

class Material;
class JottingSocialControl
{
public:
    explicit JottingSocialControl(const std::string& netizenId);
    ~JottingSocialControl();
private:
    Netizen *m_netizen;
};

#endif // JOTTINGSOCIALCONTROL_H
