#ifndef MATERIALBROKER_H
#define MATERIALBROKER_H

#include "material.h"
#include <database.h>

class MaterialBroker
{
public:
    static MaterialBroker* getInstance(){
        if(materialBroker==nullptr){
            materialBroker=new MaterialBroker();
        }
        return materialBroker;
    }

    Material* findMaterialById(int id)const;//findJoNetizenById()
private:
    MaterialBroker(){};
    static MaterialBroker *materialBroker;
    DataBase *db=DataBase::getInstance();
};

#endif // MATERIALBROKER_H
