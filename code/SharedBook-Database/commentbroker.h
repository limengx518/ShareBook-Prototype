#ifndef COMMENTBROKER_H
#define COMMENTBROKER_H

#include <QVector>

//#include "comment.h"

#include "database.h"

class Comment;
class CommentBroker
{
public:
    static CommentBroker* getInstance(){
        if(commentBroker==nullptr){
            commentBroker=new CommentBroker();
        }
        return commentBroker;
    }
    Comment *findCommentById(int comment_id);
    QVector<Comment*> findJotComment(int jotting_id);
    QVector<Comment*> findNetizenComment(int netizen_id);
    int findCommentJotById(int comment_id);
    int findCommentNetizenById(int comment_id);
    void addNewComment(Comment *comment, int j_id, int n_id) const;
private:
    CommentBroker(){};
    static CommentBroker *commentBroker;
    DataBase *db=DataBase::getInstance();
};


#endif // COMMENTBROKER_H
