#include "material.h"

Material::Material(const std::string &tid, std::string jottingId):
    MaterialInterface(tid),_jottingProxy(jottingId)
{

}

Material::Material(const std::string id, std::string jottingId, std::string path):
    MaterialInterface(id),_jottingProxy(jottingId),m_path(path)
{

}

const std::string Material::jottingId() const
{
    return _jottingProxy.id();
}

std::string Material::getAbstract()
{
    return path();
}

const std::string &Material::path() const
{
    return m_path;
}
