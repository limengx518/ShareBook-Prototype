#include "material.h"

Material::Material(const std::string &tid):
    MaterialInterface(tid)
{

}

Material::Material(const std::string id, std::string path):
    MaterialInterface(id),m_path{path}
{

}

std::string Material::path()
{
    return m_path;
}

std::string Material::getMaterialAbstract()
{
    return m_path;
}
