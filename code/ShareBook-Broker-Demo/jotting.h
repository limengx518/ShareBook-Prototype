#ifndef JOTTING_H
#define JOTTING_H

#include "jottinginterface.h"
#include <unordered_map>
#include <vector>
#include "materialproxy.h"

class Jotting : public JottingInterface
{
public:
    explicit Jotting(const std::string &tid);
    explicit Jotting(const std::string id,std::string content,std::vector<std::string> materialsId);
    virtual ~Jotting(){}

    virtual nlohmann::json getJottingAbstract() override;

private:
    std::unordered_map<std::string, MaterialProxy> _materials;
    std::string m_note;
};

#endif // JOTTING_H
