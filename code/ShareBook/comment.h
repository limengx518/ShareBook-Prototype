#ifndef COMMENT_H
#define COMMENT_H

#include <string>
#include <vector>
#include <unordered_map>
#include <nlohmann/json.hpp>
#include "materialproxy.h"
#include "jottingproxy.h"
#include "commentinterface.h"
#include "netizen.h"

class Comment:public CommentInterface
{
public:
    explicit Comment(const std::string id,std::string netizenId,std::string jottingId);
    virtual ~Comment(){}

    virtual nlohmann::json getCommentDetail() override;

private:
    NetizenProxy _netizen;
    JottingProxy _jotting;
    std::string m_content;
};

#endif // COMMENT_H
