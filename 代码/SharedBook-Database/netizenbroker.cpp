#include "netizenbroker.h"
#include "jottingbroker.h"
#include "comment.h"
#include "netizen.h"

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>


NetizenBroker* NetizenBroker::netizenBroker=NULL;

Netizen* NetizenBroker::findNetizenById(int id) const
{
    QHash<QString,QString> map=db->findNetizenById(id);
    Netizen* nt=new Netizen(map.value("id").toInt(),map.value("name"),map.value("aveter"),map.value("signal"));
    return nt;
}

//QVector<Jotting*> NetizenBroker::find_Netizen_Jottings(int netizen_id) const
//{
//    JottingBroker *jt=JottingBroker::getInstance();
//    QVector<Jotting*> jts=jt->findNetizenJotById(netizen_id);
//    return jts;
//}

QVector<Netizen *> NetizenBroker::findInterests(int netizen_id) const
{
    QVector<Netizen*> nts;
    QVector<QString> map=db->findRelationById("interested",netizen_id);
    for(auto& item:map){
        nts.append(findNetizenById(item.toInt()));
    }
    return nts;
}

QVector<Netizen *> NetizenBroker::findFans(int netizen_id) const
{
    QVector<Netizen*> nts;
    QVector<QString> map=db->findRelationById("fans",netizen_id);
    for(auto& item:map){
        nts.append(findNetizenById(item.toInt()));
    }
    return nts;
}

void NetizenBroker::addNewNetizen(Netizen *netizen) const
{
    QString inserCommend=QString("insert into Netizen (N_name,N_avater,N_signal) values('%1','%2','%3')").arg(netizen->getNickname()).arg(netizen->getAvatar()).arg(netizen->getSignal());
    db->insertData(inserCommend);
}

void NetizenBroker::addFan(int id, int fan_id) const
{
    QString inserCommend=QString("insert into Relation values(%1,%2)").arg(id).arg(fan_id);
    db->insertData(inserCommend);
}

void NetizenBroker::addInterst(int id, int interst_id) const
{
    QString inserCommend=QString("insert into Relation values(%1,%2)").arg(interst_id).arg(id);
    db->insertData(inserCommend);
}


