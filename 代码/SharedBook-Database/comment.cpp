#include "comment.h"
#include "netizen.h"
#include "jotting.h"
#include "commentbroker.h"
#include "netizenbroker.h"


Comment::Comment(int id, int likeCounter, QString date, QString content ,Netizen* netizen,Jotting* jotting):
    m_id(id),m_likeCounter(likeCounter),m_date(date),m_content(content),
    m_netizen(netizen),m_jotting(jotting)
{

}

Comment::Comment(QString date, QString content, Netizen *netizen, Jotting *jotting,int likeCounter):
    m_likeCounter(likeCounter),m_date(date),m_content(content),
    m_netizen(netizen),m_jotting(jotting)
{

}

void Comment::getCommentDetail(NetizenBroker* nb,CommentBroker* cb)
{
    if(m_netizen==nullptr){
//        qDebug()<<"cb->findCommentNetizenById(m_id))"<<cb->findCommentNetizenById(m_id);
        setNetizen(nb->findNetizenById(cb->findCommentNetizenById(m_id)));
    }

     m_netizen->get_Netizen_ID_Info();
     qDebug()<<"评论内容"<<m_content<<"   "<<"点赞数："<<m_likeCounter;
}

void Comment::setNetizen(Netizen *netizen)
{
    m_netizen=netizen;
}

QString Comment::getContent()
{
    return this->m_content;
}

int Comment::getId()
{
    return this->m_id;
}
