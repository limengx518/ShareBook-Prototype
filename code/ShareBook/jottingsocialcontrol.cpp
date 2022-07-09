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
#include "messagesequence.h"


using json = nlohmann::json;

JottingSocialControl::JottingSocialControl()
{
    m_timer.start(30000,flush);
    m_NotificationTimer.start(10000,NotificationFlush);
}

JottingSocialControl::~JottingSocialControl()
{
    m_timer.stop();
    m_NotificationTimer.stop();
    delete NetizenBroker::getInstance();
    delete JottingBroker::getInstance();
    delete CommentBroker::getInstance();
    delete MaterialBroker::getInstance();
    delete MessageSequence::getInstance();
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

bool JottingSocialControl::publishJotting(std::string netizenId, nlohmann::json jottingContent)
{
    Netizen netizen=NetizenBroker::getInstance()->findById(netizenId);
    netizen.publishJotting(jottingContent);
    return true;
}

void JottingSocialControl::follow(std::string nId, std::string concernedId)
{
    Netizen netizen=NetizenBroker::getInstance()->findById(nId);
    netizen.followNetizen(concernedId);
}

nlohmann::json JottingSocialControl::scanMessage(std::string netizenId)
{
    Netizen netizen=NetizenBroker::getInstance()->findById(netizenId);
    return netizen.scanMessages();
}

nlohmann::json JottingSocialControl::checkMessage(std::string netizenId, std::string messageId)
{
    Netizen netizen=NetizenBroker::getInstance()->findById(netizenId);
    return netizen.checkMessage(messageId);
}

void JottingSocialControl::flush()
{
    NetizenBroker::getInstance()->flush();
    JottingBroker::getInstance()->flush();
    CommentBroker::getInstance()->flush();
    MaterialBroker::getInstance()->flush();
}

void JottingSocialControl::NotificationFlush()
{
    std::cout<<"消息推送"<<std::endl;
    MessageSequence::getInstance()->updateMessageQueue();
}
