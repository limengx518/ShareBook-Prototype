#include "jottingsocialcontrol.h"
#include "comment.h"
#include "netizenbroker.h"
#include "jottingbroker.h"
#include "materialbroker.h"
#include "commentbroker.h"
#include <time.h>
#include <sstream>
#include <chrono>
#include <stdio.h>
#include <cstring>
#include <ctime>
#include <thread>
#include "material.h"


using json = nlohmann::json;

JottingSocialControl::JottingSocialControl()
{
    m_timer.start(30000,flush);
}

JottingSocialControl::~JottingSocialControl()
{
    m_timer.stop();
    delete NetizenBroker::getInstance();
    delete JottingBroker::getInstance();
    delete CommentBroker::getInstance();
    delete MaterialBroker::getInstance();
}

nlohmann::json JottingSocialControl::login(std::string netizenId)
{
    Netizen &netizen=NetizenBroker::getInstance()->findById(netizenId);
    netizen.writeLog();
    netizen.readLog();
    return netizen.getInfo();
}

nlohmann::json JottingSocialControl::pushJottings(std::string netizenId)
{
    Netizen &netizen=NetizenBroker::getInstance()->findById(netizenId);
    return netizen.scanJottings();
}

nlohmann::json JottingSocialControl::checkOneJotting(std::string netizenId, std::string jottingId)
{
    Netizen &netizen=NetizenBroker::getInstance()->findById(netizenId);
    return netizen.checkOneJotting(jottingId);
}

bool JottingSocialControl::comment(std::string netizenId, std::string jottingId, std::string content)
{
    Netizen &netizen=NetizenBroker::getInstance()->findById(netizenId);
    netizen.comment(content,jottingId);
    return true;
}

void JottingSocialControl::flush()
{
    NetizenBroker::getInstance()->flush();
    JottingBroker::getInstance()->flush();
    CommentBroker::getInstance()->flush();
    MaterialBroker::getInstance()->flush();

}

