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
    m_netizen=&NetizenBroker::getInstance()->findNetizenById(id);
    m_netizen->getInfo();
    getSomeJottings("1","2");
    sendChooseMaterialRequest();
    sendPreviewRequest();
}

void JottingSocialControl::getSomeJottings(std::string lastTime, std::string thisTime)
{
    JottingBroker *jottingbroker = JottingBroker::getInstance();
    std::vector<std::string> jottingsId=jottingbroker->getSomeJottingsId(lastTime,thisTime);

    for(auto id:jottingsId)
        _jottings.insert(std::pair<std::string,JottingProxy>(id,JottingProxy(id)));

    json jottings;
    for(auto &item:_jottings){
        json jotting=item.second.getJottingAbstract();
        jottings[item.first]["content"]=jotting["content"];
        jottings[item.first]["material"]=jotting["material_firstPath"];
    }
    std::cout<<jottings.dump(4)<<std::endl;

}

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y%m%d%X", &tstruct);
    return buf;
}

void JottingSocialControl::sendChooseMaterialRequest()
{
    std::string now =currentDateTime();
    now.erase(std::find(now.begin(), now.end(), ':'));
    now.erase(std::find(now.begin(), now.end(), ':'));
    m_materials.push_back(Material(now,"path4"));
}

JottingSocialControl::~JottingSocialControl()
{
    if(m_netizen!=nullptr)
        delete m_netizen;
}

std::string JottingSocialControl::getJottingContents()
{
    return "water water water";
}

void JottingSocialControl::sendPreviewRequest()
{
    json jottingInfo;
    jottingInfo["netizenName"]=m_netizen->nickName();
    jottingInfo["content"]=getJottingContents();
    for(auto &m:m_materials){
         jottingInfo["materials"][m.id()]=m.path();
    }
    std::cout<< jottingInfo.dump(4)<<std::endl;
}

void JottingSocialControl::sendPublishRequest()
{
    std::string now =currentDateTime();
    now.erase(std::find(now.begin(), now.end(), ':'));
    now.erase(std::find(now.begin(), now.end(), ':'));
    std::vector<std::string> materialId;
    for(auto& item:m_materials){
        materialId.push_back(item.id());
    }
    m_newJotting=new Jotting(now,getJottingContents(),materialId);
    JottingBroker::getInstance()->addNewJotting(m_newJotting);
    for(auto &item:m_materials){
        MaterialBroker::getInstance()->addNewMaterial(&item);
    }
}
