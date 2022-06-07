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
        std::string id,content,nid,jid;
         // Loop through and print results
        while (res->next()) {
            id=std::to_string(res->getInt(1));
            content=res->getString(2);
            nid=std::to_string(res->getInt(3));
            jid=res->getString(4);
        }
        //retrieveComment(id)
        Comment *comment=new Comment(id,content,nid,jid);

        storeObject(*comment);
        return comment;
    }
    std::cout<<"in cache"<<std::endl;
    return comment;
}


Comment* CommentBroker::inCache(std::string objectId)
{
    std::unordered_map<std::string,std::string> m=RelationalBroker::inCache("comment"+objectId);
    if(m.empty())
        return nullptr;
    Comment* comment=new Comment(objectId,m["content"],m["publisherId"],m["jottingId"]);

    return comment;
}

void CommentBroker::storeObject(const Comment &comment)
{
    std::unordered_map<std::string,std::string> map{
        {"content", comment.content()},
        {"publisherId", comment.publisherId()},
        {"jottingId", comment.jottingId()},
    };
    RelationalBroker::storeObject("comment"+comment.id(),map);
}

void CommentBroker::addComment(const Comment &comment)
{
    std::string id,content,n_id,j_id;
    id=comment.id();
    content=comment.content();
    n_id=comment.publisherId();
    j_id=comment.jottingId();

    std::string command="insert into Comment (C_id,C_content,N_id,J_id) values('"+id+"','"+content+"','"+n_id+"','"+j_id+"')";

    std::cout<<command<<std::endl;
    RelationalBroker::add(command);
    storeObject(comment);
}

CommentBroker::CommentBroker()
{

}
