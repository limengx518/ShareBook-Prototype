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
#include "material.h"



using json = nlohmann::json;

JottingSocialControl::JottingSocialControl()
{
}

JottingSocialControl::~JottingSocialControl()
{
}

void JottingSocialControl::login(std::string netizenId)
{
    Netizen *netizen=NetizenBroker::getInstance()->findById(netizenId);
    netizen->getInfo();
}

void JottingSocialControl::pushJottings(std::string lastTime, std::string thisTime)
{
    std::vector<std::string> jottingsId=JottingBroker::getInstance()->getSomeJottingsId(lastTime,thisTime);

    std::vector<JottingProxy> jottings;
    for(const auto &item:jottingsId){
        jottings.push_back(JottingProxy(item));
    }

    for(auto& jotting:jottings){
        std::cout<<jotting.getAbstract().dump(4)<<std::endl;
    }

}

void JottingSocialControl::checkOneJotting(std::string objectId)
{
    JottingProxy jotting=JottingProxy(objectId);
    std::cout<<jotting.getDetail().dump(4)<<std::endl;
}

void JottingSocialControl::addComment(std::string netizenId, std::string jottingId, std::string content)
{
    auto now = std::chrono::system_clock::now();
    auto t_c = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss<<std::put_time(std::localtime(&t_c), "%F %T");
    std::string time_string=ss.str();
    time_string.erase(std::find(time_string.begin(), time_string.end(), '-'));
    time_string.erase(std::find(time_string.begin(), time_string.end(), '-'));

    Comment comment(time_string,content,netizenId,jottingId);
    CommentBroker::getInstance()->addComment(comment);
}

