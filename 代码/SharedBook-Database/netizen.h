#ifndef NETIZEN_H
#define NETIZEN_H

#include <QString>
#include <QDebug>

#include "jotting.h"
#include "netizenbroker.h"

class MaterialBroker;
class JottingBroker;

class Netizen
{
public:
    Netizen();
    Netizen(int id,QString nickname,QString avatar,QString signal);
    int getID();
    void get_Netizen_ID_Info();

    void getAllJotDig(NetizenBroker *nb,MaterialBroker *mb,JottingBroker *jb);
    void setJottings(QVector<Jotting*> jottings);

    void setFans(QVector<Netizen*> fans);
    QVector<Netizen*> getFans();
    void get_Fans_ID_Info();

    void setInterests(QVector<Netizen*> interests);
    QVector<Netizen*> getInterests();
    void get_Interests_ID_Info();

    QString getNickname();

    void pushInterestsJotting(NetizenBroker *nb,JottingBroker *jb,MaterialBroker *mb);

private:
    int m_id;
    QString m_nickname;
    QString m_avatar;
    QString m_signal;

    QVector<Jotting *> m_jottings;
    QVector<Netizen *> m_fans;
    QVector<Netizen *> m_interests;
};

#endif // NETIZEN_H
