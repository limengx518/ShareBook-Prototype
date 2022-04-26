#ifndef NETIZEN_H
#define NETIZEN_H

#include <QString>
#include <QDebug>

#include "jotting.h"
#include "netizenbroker.h"

class MaterialBroker;
class JottingBroker;
class Comment;

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

    void addPostedCom(NetizenBroker* nb,Comment* comment);
    QString getNickname();

    QVector<Jotting*> pushInterestsJotting(JottingBroker* jb);

private:
    int m_id;
    QString m_nickname;
    QString m_avatar;
    QString m_signal;

    QVector<Jotting *> m_jottings;
    QVector<Netizen *> m_fans;
    QVector<Netizen *> m_interests;
    QVector<Comment*> m_postedComment;
};

#endif // NETIZEN_H
