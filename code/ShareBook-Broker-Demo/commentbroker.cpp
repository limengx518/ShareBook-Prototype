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

        //更新缓存
        update();
        //将从数据库中拿出的数据放在缓存中(旧的净缓存)
        m_oldClean.insert({comment->id(),*comment});
        m_newCleanId.insert(comment->id());

        return comment;
    }
    std::cout<<"in cache"<<std::endl;
    return comment;
}

void CommentBroker::addComment(const Comment &comment)
{
    std::string id,content,n_id,j_id;
    id=comment.id();
    content=comment.content();
    n_id=comment.publisherId();
    j_id=comment.jottingId();

    std::string command="insert into Comment (C_id,C_content,N_id,J_id) values('"+id+"','"+content+"','"+n_id+"','"+j_id+"')";

//    //更新缓存
//    update();
//    //将从数据库中拿出的数据放在缓存中(旧的净缓存)
//    m_oldClean.insert({jotting->id(),*jotting});

    std::cout<<command<<std::endl;

}

Comment *CommentBroker::inCache(std::string id)
{
    if(m_oldClean.find(id)!=m_oldClean.end()){
        //返回comment的引用
        return &m_oldClean.find(id)->second;
    }

    if(m_newClean.find(id)!=m_newClean.end()){
        //返回comment的引用
        return &m_newClean.find(id)->second;
    }

    return nullptr;
}

void CommentBroker::update()
{
    //判断缓存大小是否达到最大值，若为最大则删除部分comment对象
    if(m_newClean.size()==MAX_CAPACITY){
        for(int i=0;i<DELETE_COUNT;i++){
            //获取要删除的commentId
            auto comment_id=m_newCleanId.begin();

            //将newClean里的comment存入数据库
            auto comment=m_newClean.at(*comment_id);
            std::string command="insert into Comment (C_id,C_content,N_id,J_id) values("+comment.id()+","+comment.content()+","+comment.publisherId()+","+comment.jottingId()+")";
            RelationalBroker::insert(command);

            //将指定comment以及commentId进行删除
            m_newClean.erase(*comment_id);
            m_newCleanId.erase(comment_id);
        }
    }

    if(m_oldClean.size()==MAX_CAPACITY){
        for(int i=0;i<DELETE_COUNT;i++){
            auto comment_id=m_oldCleanId.begin();
            m_oldClean.erase(*comment_id);
            m_oldCleanId.erase(comment_id);
        }
    }
}

CommentBroker::~CommentBroker()
{
    //程序退出后，将缓存中的新数据存入数据库
    for(auto &comment:m_newClean){
        std::string command="insert into Comment (C_id,C_content,N_id,J_id) values("+comment.second.id()+","+comment.second.content()+","+comment.second.publisherId()+","+comment.second.jottingId()+")";
        RelationalBroker::insert(command);
    }
}

CommentBroker::CommentBroker()
{

}
