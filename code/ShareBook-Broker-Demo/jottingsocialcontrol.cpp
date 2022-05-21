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



using json = nlohmann::json;

JottingSocialControl::JottingSocialControl(const std::string &id)
{
    m_netizen=NetizenBroker::getInstance()->findById(id);
    m_netizen->getInfo();
}

JottingSocialControl::~JottingSocialControl()
{
}

