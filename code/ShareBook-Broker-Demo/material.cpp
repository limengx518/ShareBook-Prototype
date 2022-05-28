#include "material.h"

Material::Material(const std::string &tid, std::string jottingId):
    MaterialInterface(tid),_jottingProxy(jottingId)
{

}

Material::Material(const std::string id, std::string jottingId, std::string path):
    MaterialInterface(id),_jottingProxy(jottingId),m_path(path)
{

}


std::string Material::path()
{
    return m_path;
}

std::string Material::getAbstract()
{
    return m_path;
}
