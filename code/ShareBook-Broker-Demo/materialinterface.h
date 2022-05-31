#ifndef MATERIALINTERFACE_H
#define MATERIALINTERFACE_H

#include <iostream>

class MaterialInterface
{
public:
    explicit MaterialInterface(const std::string &tid);
    virtual  ~MaterialInterface(){}

    virtual std::string getAbstract()  = 0;
    const std::string id() const;
private:
    std::string m_timeId;
};

#endif // MATERIALINTERFACE_H
