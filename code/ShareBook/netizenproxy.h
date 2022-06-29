#ifndef NETIZENPROXY_H
#define NETIZENPROXY_H

#include "netizeninterface.h"

class Netizen;

class NetizenProxy:public NetizenInterface
{
public:
    explicit NetizenProxy(const std::string &tid);
    virtual ~NetizenProxy();
    virtual nlohmann::json getAbstract() override;
private:
    Netizen *_netizen;
};
#endif // NETIZENPROXY_H
