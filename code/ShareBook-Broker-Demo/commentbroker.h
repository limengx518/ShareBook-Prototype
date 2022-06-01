#ifndef COMMENTBROKER_H
#define COMMENTBROKER_H

#include <vector>
#include <unordered_map>

#include "commentinterface.h"
#include "relationalbroker.h"
#include "cache.h"
#include "comment.h"

class CommentBroker : public RelationalBroker
{
public:
    static CommentBroker *getInstance();

    Comment *findById(std::string id);
    std::vector<std::string> getSomeCommentsId(std::string lastTime,std::string thisTime);

    Comment* inCache(std::string objectId);
    void storeObject(const Comment& Comment);

    virtual ~CommentBroker(){};
private:
    CommentBroker();
    static CommentBroker* m_CommentBroker;
};

#endif // COMMENTBROKER_H
