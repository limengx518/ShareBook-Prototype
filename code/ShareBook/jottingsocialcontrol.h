#ifndef JOTTINGSOCIALCONTROL_H
#define JOTTINGSOCIALCONTROL_H

#include "netizen.h"
#include <unordered_map>
#include "personaluicontrol.h"


class PersonalUIControl;
class Material;
class JottingSocialControl
{
public:
    explicit JottingSocialControl(const std::string& netizenId);
    ~JottingSocialControl();
private:
    Netizen *m_netizen;
//    PersonalUIControl *m_personalUIControl;
};

#endif // JOTTINGSOCIALCONTROL_H
