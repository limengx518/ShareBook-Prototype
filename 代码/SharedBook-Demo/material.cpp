#include "material.h"
#include "jotting.h"
#include <iostream>

Material::Material(int id,std::vector<std::string> pictures)
{
    this->m_materialid = id;
    this->m_pictures = pictures;
}

void Material::getMaterialDig()
{
    for(auto & pic:this->m_pictures)
        std::cout<<pic<<"  ";
}

void Material::setJotting(Jotting *jot)
{
    this->m_jotting = jot;
}

int Material::getMaterialId()
{
    return this->m_materialid;
}
