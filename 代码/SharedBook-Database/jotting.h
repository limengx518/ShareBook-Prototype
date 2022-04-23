#ifndef JOTTING_H
#define JOTTING_H

#include <QString>
#include <QDebug>

class MaterialBroker;
class Netizen;
class Material;
class JottingBroker;
class NetizenBroker;

class Jotting
{
public:
    Jotting();
    Jotting(int id,QString time,QString text,Netizen *publisher=nullptr,Material *material=nullptr);

    void getJotDig(NetizenBroker *nb,MaterialBroker *mb,JottingBroker * jb);
    void setMaterial(Material *material);

    Netizen getPublisher();
    void setPublisher(Netizen *publisher);

    int getID();
    void setId(int id);
private:
    int m_id;
    QString m_time;
    QString m_text;

    Netizen *m_publisher;
    Material *m_material;
};

#endif // JOTTING_H
