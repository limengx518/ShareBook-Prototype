#ifndef JOTTINGSOCIALCONTROL_H
#define JOTTINGSOCIALCONTROL_H

#include <QVector>

class Netizen;
class Jotting;
class NetizenBroker;
class JottingBroker;
class CommentBroker;
class MaterialBroker;


class JottingSocialControl
{
public:
    JottingSocialControl();
    void login(int id);
    void pushJottings();
private:
    NetizenBroker *nb;
    JottingBroker *jb;
    CommentBroker *cb;
    MaterialBroker *mb;
    Netizen *m_netizen;

    //Jotting buffer storage in here
    QVector<Jotting* > m_jottings;
};

#endif // JOTTINGSOCIALCONTROL_H
