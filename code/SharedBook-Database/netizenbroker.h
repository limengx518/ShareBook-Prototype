#ifndef NETIZENBROKER_H
#define NETIZENBROKER_H

#include <QVector>
#include <database.h>

class Netizen;
class Jotting;


class NetizenBroker
{
public:
    static NetizenBroker* getInstance(){
        if(netizenBroker==nullptr){
            netizenBroker=new NetizenBroker();
        }
        return netizenBroker;
    }

    Netizen* findNetizenById(int id)const;//findJoNetizenById()

//    QVector<Jotting*> find_Netizen_Jottings(int netizen_id)const;

    QVector<Netizen*> findInterests(int netizen_id)const;
    QVector<Netizen*> findFans(int netizen_id)const;

    void addNewNetizen(Netizen *netizen)const;    //修改
    void addFan(int id,int fan_id)const;
    void addInterst(int id,int interst_id)const;

private:
    NetizenBroker(){};
    static NetizenBroker *netizenBroker;
    DataBase *db=DataBase::getInstance();
};
#endif // NETIZENBROKER_H
