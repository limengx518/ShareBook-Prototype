#ifndef COMMENTBROKER_H
#define COMMENTBROKER_H

#include "broker.h"
//#include "comment.h"
#include <vector>

class Comment;

class CommentBroker : public Broker
{
public:
    CommentBroker();
private:
    std::vector<Comment> m_comments;
};

#endif // COMMENTBROKER_H
