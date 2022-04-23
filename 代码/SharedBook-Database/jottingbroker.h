#ifndef JOTTINGBROKER_H
#define JOTTINGBROKER_H

#include <vector>
#include "database.h"

class Material;
class Jotting;
class Netizen;
class Comment;

using namespace std;

class JottingBroker//:public Broker
{
public:
    static JottingBroker* getInstance(){
        if(jottingBroker==nullptr){
            jottingBroker=new JottingBroker();
        }
        return jottingBroker;
    }

    Jotting* findJottingById(int jottingid)const;

    int findMatrialByID(int jotting_id)const;    //修改
    //找jotting的netizen
    int findJotPublisher(int jotting_id)const;   //修改

    QVector<Jotting*> findSomeJottings();

    //找netizen的jottings
    QVector<Jotting*> findNetizenJotById(int n_id)const;

private:
    JottingBroker(){};
    static JottingBroker *jottingBroker;
    DataBase *db=DataBase::getInstance();
//    DataBase db;

};

#endif // JOTTINGBROKER_H
