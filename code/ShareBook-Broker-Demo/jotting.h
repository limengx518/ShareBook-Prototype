#ifndef JOTTING_H
#define JOTTING_H

#include "jottinginterface.h"
#include <unordered_map>
#include <vector>
#include "materialproxy.h"
#include "netizenproxy.h"

class Jotting : public JottingInterface
{
public:
    explicit Jotting(const std::string &tid,std::string netizenId);
    explicit Jotting(const std::string id,std::string content,std::string netizenId,std::vector<std::string> materialsId);
    virtual ~Jotting(){}

    virtual nlohmann::json getAbstract() override;


    const std::string note() const;
    const std::string netizenId() const;
    const std::vector<std::string> materialId() const;

private:
    NetizenProxy _netizenProxy;
    std::unordered_map<std::string, MaterialProxy> _materials;
    std::string m_note;
};

#endif // JOTTING_H
