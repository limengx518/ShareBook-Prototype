#ifndef NETIZENINTERFACE_H
#define NETIZENINTERFACE_H

#include <iostream>
#include <nlohmann/json.hpp>

class NetizenInterface
{
public:
    explicit NetizenInterface(const std::string &tid);
    virtual ~NetizenInterface(){}

    virtual nlohmann::json getNetizenAbstract()  = 0;
    std::string id() const;
private:
    std::string m_id;
};

#endif // NETIZENINTERFACE_H
