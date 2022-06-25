#include "jottingsocialcontrol.h"
#include "netizenbroker.h"
#include "jottingbroker.h"
#include "materialbroker.h"
#include <time.h>
#include <sstream>
#include <chrono>
#include <stdio.h>
#include <cstring>
#include "material.h"
#include "personaluicontrol.h"

using json = nlohmann::json;

JottingSocialControl::JottingSocialControl(){

//    m_personalUIControl=new PersonalUIControl(m_netizen->getInfo());
//    m_netizen->getInfo();
}

JottingSocialControl::~JottingSocialControl()
{
}

void JottingSocialControl::login(std::string id)
{
   Netizen*  m_netizen=NetizenBroker::getInstance()->findById(id);
   m_netizen->getInfo();

}

