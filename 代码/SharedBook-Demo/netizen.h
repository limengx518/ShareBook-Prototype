#ifndef NETIZEN_H
#define NETIZEN_H

#include "jotting.h"
#include "netizenbroker.h"

#include <unordered_map>
#include <string>
class MaterialBroker;
class JottingBroker;

class Netizen
{
public:
    Netizen();
    Netizen(int id,std::string nickname,std::string avatar,std::string signal);
    int getID();
    void get_Netizen_ID_Info();

    void getAllJotDig(NetizenBroker *nb,MaterialBroker *mb);
    void setJottings(std::vector<Jotting> jottings);

    void setFans(std::vector<Netizen> fans);
    std::vector<Netizen> getFans();
    void get_Fans_ID_Info();

    void setInterests(std::vector<Netizen> interests);
    std::vector<Netizen> getInterests();
    void get_Interests_ID_Info();

    std::string getNickname();

    void pushInterestsJotting(NetizenBroker *nb,JottingBroker *jb,MaterialBroker *mb);

private:
    int m_id;
    std::string m_nickname;
    std::string m_avatar;
    std::string m_signal;
    std::vector<Jotting> m_jottings;
    std::vector<Netizen> m_fans;
    std::vector<Netizen> m_interests;
};

#endif // NETIZEN_H
