#include "commentbroker.h"

#include <QDebug>
#include "comment.h"
CommentBroker* CommentBroker::commentBroker=NULL;

Comment *CommentBroker::findCommentById(int comment_id)
{
    QHash<QString,QString> map=db->findCommentById(comment_id);
    // Comment(int id,int likeCounter,QString date,QString content);
    Comment *cm=new Comment(map.value("id ").toInt(),map.value("likeCount").toInt(),map.value("time"),map.value("content"));
    return cm;
}

QVector<Comment *> CommentBroker::findJotComment(int jotting_id)
{
    QVector<Comment*> cms;
    QVector<QHash<QString, QString>> maps=db->findCommentByJot_NetizenId("jotting",jotting_id);
    for(auto& map:maps){
        Comment *cm=new Comment(map.value("id").toInt(),map.value("likeCount").toInt(),map.value("time"),map.value("content"));

        cms.append(cm);
    }
    return cms;
}

QVector<Comment *> CommentBroker::findNetizenComment(int netizen_id)
{
    QVector<Comment*> cms;
    QVector<QHash<QString, QString>> maps=db->findCommentByJot_NetizenId("netizen",netizen_id);
    for(auto& map:maps){
        Comment *cm=new Comment(map.value("id ").toInt(),map.value("likeCount").toInt(),map.value("time"),map.value("content"));
        cms.append(cm);
    }
    return cms;
}

int CommentBroker::findCommentJotById(int comment_id)
{
    QHash<QString,QString> map=db->findCommentById(comment_id);
    return map.value("jottingId").toInt();
}

int CommentBroker::findCommentNetizenById(int comment_id)
{
    QHash<QString,QString> map=db->findCommentById(comment_id);

    return map.value("netizenId").toInt();

}
