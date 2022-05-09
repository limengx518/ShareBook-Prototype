#ifndef COMMENT_H
#define COMMENT_H

#include <QDebug>
#include <QString>

class Netizen;
class Jotting;
class CommentBroker;
class NetizenBroker;

class Comment
{
public:
    Comment(int id,int likeCounter,QString date,QString content,Netizen* netizen=nullptr,Jotting* jotting=nullptr);
    Comment(QString date,QString content,Netizen* netizen=nullptr,Jotting* jotting=nullptr,int likeCounter=0);

    void getCommentDetail(NetizenBroker* nb,CommentBroker* cb);
    void setNetizen(Netizen* netizen);
    QString getContent();
    int getId();
    int getLikeCounter();
    QString getDate();

private:
    int m_id;
    int m_likeCounter;
    QString m_date;
    QString m_content;

    Netizen* m_netizen;
    Jotting* m_jotting;
};

#endif // COMMENT_H
