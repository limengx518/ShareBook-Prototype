#include "comment.h"

using json = nlohmann::json;

Comment::Comment(const std::string id, std::string netizenId, std::string jottingId):
    CommentInterface(id),_netizen(netizenId),_jotting(jottingId)
{

}

nlohmann::json Comment::getCommentDetail()
{
    json commentInfo;
    commentInfo["content"]=m_content;
    commentInfo["netizen"]["nikeName"]=_netizen.getNetizenAbstract()["nickName"];
    return commentInfo;
}

