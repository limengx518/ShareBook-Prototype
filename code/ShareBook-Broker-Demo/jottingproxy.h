#ifndef JOTTINGPROXY_H
#define JOTTINGPROXY_H

#include "jottinginterface.h"
#include <memory>

class Jotting;

class JottingProxy : public JottingInterface
{
public:
    explicit JottingProxy(const std::string &tid);
    virtual ~JottingProxy();
    virtual nlohmann::json getAbstract() override;

private:
    Jotting* _jotting;
};

#endif // JOTTINGPROXY_H
