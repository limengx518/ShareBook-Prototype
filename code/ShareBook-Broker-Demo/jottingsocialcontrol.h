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
    void getSomeJottings(std::string lastTime,std::string thisTime);
    void sendChooseMaterialRequest();
    ~JottingSocialControl();
    std::string getJottingContents();
    void sendPreviewRequest();
    void sendPublishRequest();
    void commentJotting(std::string id);
private:
    Netizen *m_netizen;
    std::unordered_map<std::string,JottingProxy> _jottings;
    std::vector<Material> m_materials;
    Jotting *m_newJotting;
};

#endif // JOTTINGSOCIALCONTROL_H
