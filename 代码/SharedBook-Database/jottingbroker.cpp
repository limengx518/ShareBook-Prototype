#include "jottingbroker.h"
#include "jotting.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <ctime>
#include <cstdlib>

JottingBroker* JottingBroker::jottingBroker=NULL;

Jotting* JottingBroker::findJottingById(int jottingid) const
{
    QHash<QString,QString> map=db->findJottingById(jottingid);
    Jotting* jt=new Jotting(map.value("id").toInt(),map.value("date"),map.value("text"));
    return jt;
}

int JottingBroker::findMatrialByID(int jotting_id) const
{
    QHash<QString,QString> map=db->findJottingById(jotting_id);
    return map.value("materialId").toInt();
}

int JottingBroker::findJotPublisher(int jotting_id) const
{
    QHash<QString,QString> map=db->findJottingById(jotting_id);
    return map.value("netizenId").toInt();
}

QVector<Jotting *> JottingBroker::findSomeJottings()
{
   QVector<Jotting*> jts;
//   srand((unsigned)time(NULL));
   for(int i=1;i<=8;i++){
//       int r=rand()%9+1;
       jts.push_back(findJottingById(i));
   }
   return jts;

}

QVector<Jotting*> JottingBroker::findNetizenJotById(int n_id) const
{
    QVector<QHash<QString, QString>> map=db->findNetizenJots(n_id);
    QVector<Jotting*> jts;
    for(auto &item:map){
        Jotting* jt=new Jotting(item.value("id").toInt(),item.value("date"),item.value("text"));
        jts.push_back(jt);
    }
    return jts;
}
