#ifndef MATERIAL_H
#define MATERIAL_H

#include "materialinterface.h"
#include "jottingproxy.h"

class Material:public MaterialInterface
{
public:
    explicit Material(const std::string &tid,std::string jottingId);
    explicit Material(const std::string id,std::string jottingId,std::string path);
    virtual ~Material(){}

    const std::string jottingId() const;
    virtual std::string getAbstract() override;
    const std::string &path() const;

private:
    JottingProxy _jottingProxy;
    std::string m_path;
};

#endif // MATERIAL_H
