#ifndef JOTTING_H
#define JOTTING_H

#include "commentproxy.h"
#include "jottinginterface.h"
#include <unordered_map>
#include <vector>
#include "materialproxy.h"
#include "netizenproxy.h"

class Jotting : public JottingInterface
{
public:
    explicit Jotting(const std::string &tid,std::string netizenId);
    explicit Jotting(const std::string id,std::string content,std::string time,std::string netizenId,std::vector<std::string> materialsId,std::vector<std::string> commentsId);
    virtual ~Jotting(){}

    virtual nlohmann::json getAbstract() override;
    virtual nlohmann::json getDetail() override;

    const std::string note() const;
    const std::string time() const;
    const std::string netizenId() const;
    const std::vector<std::string> materialId() const;
    const std::vector<std::string> commentId() const;

private:
    NetizenProxy _netizenProxy;
    std::unordered_map<std::string, MaterialProxy> _materials;
    std::unordered_map<std::string, CommentProxy> _comments;
    std::string m_time;
    std::string m_content;
};

#endif // JOTTING_H
