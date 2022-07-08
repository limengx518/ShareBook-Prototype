#ifndef COMMENTBROKER_H
#define COMMENTBROKER_H

#include <vector>
#include <unordered_map>
#include <set>

#include "commentinterface.h"
#include "relationalbroker.h"
#include "comment.h"

class CommentBroker : public RelationalBroker
{
public:
    static CommentBroker *getInstance();

    Comment *findById(std::string id);
    std::vector<std::string> getSomeCommentsId(std::string lastTime,std::string thisTime);

    void addComment(const Comment& comment);

    virtual ~CommentBroker();
private:
    CommentBroker();
    static CommentBroker* m_CommentBroker;

    Comment* inCache(std::string id);

    std::unordered_map<std::string,Comment> m_newClean;

    std::unordered_map<std::string,Comment> m_oldClean;


};

#endif // COMMENTBROKER_H
