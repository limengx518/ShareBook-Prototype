#include "material.h"
#include "jotting.h"
#include <iostream>

Material::Material(int id,QString materials)
{
    this->m_materialId = id;
    this->m_materials = materials;
}

void Material::getMaterialDetail()
{
    qDebug()<<"所有素材信息："<<m_materials;
}

void Material::getMaterialDig()
{
//    for(auto & pic:this->m_materials)
//         qDebug()<<pic<<"  ";
    qDebug()<<"素材信息："<<m_materials;
}

void Material::setJotting(Jotting *jot)
{
    this->m_jotting = jot;
}

int Material::getMaterialId()
{
    return this->m_materialId;
}
