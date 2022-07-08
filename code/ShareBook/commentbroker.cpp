#include "commentbroker.h"

#include <unordered_map>
#include <sstream>
#include <string>
#include <vector>

CommentBroker* CommentBroker::m_CommentBroker=NULL;

CommentBroker *CommentBroker::getInstance()
{
    if(m_CommentBroker==nullptr){
        m_CommentBroker=new CommentBroker();
    }
    return m_CommentBroker;
}

Comment *CommentBroker::findById(std::string id)
{
    Comment* comment=inCache(id);
    if(comment == nullptr){
        std::string command="select * from Comment where C_id="+id;
        sql::ResultSet* res=RelationalBroker::query(command);
        std::string id,content,time,nid,jid;
         // Loop through and print results
        while (res->next()) {
            id=std::to_string(res->getUInt(1));
            content=res->getString(2);
            time=res->getString(3);
            nid=std::to_string(res->getUInt(4));
            jid=std::to_string(res->getUInt(5));
        }
        //retrieveComment(id)
        comment=new Comment(id,content,time,nid,jid);

        //将从数据库中拿出的数据放在缓存中(旧的净缓存)
        m_oldClean.insert({comment->id(),*comment});
    }

    return comment;
}

void CommentBroker::addComment(const Comment &comment)
{
//    std::string id,content,n_id,j_id;
//    id=comment.id();
//    content=comment.content();
//    n_id=comment.publisherId();
//    j_id=comment.jottingId();

//    std::string command="insert into Comment (C_id,C_content,N_id,J_id) values('"+id+"','"+content+"','"+n_id+"','"+j_id+"')";

    //将从数据库中拿出的数据放在缓存中(旧的净缓存)
    m_newClean.insert({comment.id(),comment});

//    std::cout<<command<<std::endl;

}

Comment *CommentBroker::inCache(std::string id)
{
    //判断是否在缓存中
    if(m_oldClean.count(id)){
        return &m_oldClean.at(id);
    }

    if(m_newClean.count(id)){
        return &m_newClean.at(id);
    }

    return nullptr;
}

CommentBroker::~CommentBroker()
{
    //程序退出后，将缓存中的新数据存入数据库
    for(auto &comment:m_newClean){
        std::string command="insert into Comment (C_id,C_content,C_time,N_id,J_id) values("+comment.second.id()+","+comment.second.content()+","+comment.second.publisherId()+","+comment.second.jottingId()+")";
        RelationalBroker::insert(command);
    }
}

CommentBroker::CommentBroker()
{

}
