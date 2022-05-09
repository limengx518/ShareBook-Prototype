#ifndef JOTTING_H
#define JOTTING_H

#include <string>

class MaterialBroker;
class Netizen;
class Material;
class JottingBroker;
class NetizenBroker;

class Jotting
{
public:
    Jotting(int id,std::string time,std::string text,Netizen *publisher=nullptr,Material *material=nullptr);
    void getJotDig(NetizenBroker *nb,MaterialBroker *mb);
    int getID();
    void setMaterial(Material *material);
    Netizen getPublisher();
    void setPublisher(Netizen *publisher);
private:
    int m_id;
    Netizen *m_publisher;
    Material *m_material;
    std::string m_time;
    std::string m_text;
};

#endif // JOTTING_H
