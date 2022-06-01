#ifndef COMMENT_H
#define COMMENT_H

#include <unordered_map>
#include <vector>

#include "commentinterface.h"
#include "jottingproxy.h"
#include "materialproxy.h"
#include "netizenproxy.h"

class Comment: public CommentInterface
{
public:
//    explicit Comment(const std::string &tid,std::string publisherId);
    explicit Comment(const std::string id,std::string content,std::string publisherId,std::string jottingId);
    virtual ~Comment(){}

    virtual nlohmann::json getInfo() override;

    const std::string content() const;
    const std::string publisherId() const;
    const std::string jottingId() const;

private:
    NetizenProxy _netizenProxy;
    JottingProxy _jottingProxy;
    std::string m_content;
};

#endif // COMMENT_H
