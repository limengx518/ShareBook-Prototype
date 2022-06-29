#ifndef COMMENTBROKER_H
#define COMMENTBROKER_H

#include <vector>
#include <unordered_map>
#include <set>

#include "commentinterface.h"
#include "relationalbroker.h"
#include "comment.h"

#define MAX_CAPACITY 30
#define DELETE_COUNT 15

class CommentBroker : public RelationalBroker
{
public:
    static CommentBroker *getInstance();

    Comment *findById(std::string id);
    std::vector<std::string> getSomeCommentsId(std::string lastTime,std::string thisTime);

    void addComment(const Comment& comment);

    Comment* inCache(std::string id);
    Comment* inCache(std::unordered_map<std::string,Comment>& cache,std::set<std::string>& cacheId,std::string id);

    void update() override;

    void commentIsExistInNew(std::string id);
    virtual ~CommentBroker();
private:
    CommentBroker();
    static CommentBroker* m_CommentBroker;

    std::unordered_map<std::string,Comment> m_newClean;
    std::set<std::string> m_newCleanId;

    std::unordered_map<std::string,Comment> m_oldClean;
    std::set<std::string> m_oldCleanId;


};

#endif // COMMENTBROKER_H
