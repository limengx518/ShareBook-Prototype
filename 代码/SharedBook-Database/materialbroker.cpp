#include "materialbroker.h"
#include <QDebug>

MaterialBroker* MaterialBroker::materialBroker=NULL;

Material* MaterialBroker::findMaterialById(int id) const
{
    QHash<QString,QString> map=db->findMaterialById(id);

    Material* ma=new Material(map.value("id").toInt(),map.value("pictures"));
    return ma;
}

