#ifndef MATERIAL_H
#define MATERIAL_H

#include "materialinterface.h"

class Material:public MaterialInterface
{
public:
    explicit Material(const std::string &tid);
    explicit Material(const std::string id,std::string path);
    virtual ~Material(){}
    std::string path();

    virtual std::string getMaterialAbstract() override;
private:
    std::string m_path;
};

#endif // MATERIAL_H
