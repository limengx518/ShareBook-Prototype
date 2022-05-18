#include "jottingsocialcontrol.h"
#include "netizenbroker.h"

JottingSocialControl::JottingSocialControl(const std::string &id)
{
    m_netizen=&NetizenBroker::getInstance()->findNetizenById(id);
    m_netizen->getInfo();
}
