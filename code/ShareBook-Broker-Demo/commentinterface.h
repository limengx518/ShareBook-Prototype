#ifndef COMMENTINTERFACE_H
#define COMMENTINTERFACE_H

#include <string>
#include <nlohmann/json.hpp>

class CommentInterface
{
public:
    explicit CommentInterface(const std::string &tid);
    virtual ~CommentInterface(){}

    virtual nlohmann::json getCommentDetail()= 0;
    std::string id() const;
private:
    std::string m_timeId;
};

#endif // COMMENTINTERFACE_H
