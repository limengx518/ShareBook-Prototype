#ifndef NETIZEN_H
#define NETIZEN_H

#include <unordered_map>
#include <string>
#include "commentproxy.h"
#include "jottingproxy.h"
#include <vector>
#include "netizeninterface.h"
#include "netizenproxy.h"

class Netizen:public NetizenInterface
{
public:
    explicit Netizen(const std::string& tid);
    explicit Netizen(const std::string id, std::string nickName, std::vector<std::string> jottingId,std::vector<std::string> fansId, std::vector<std::string> conceredsId,std::vector<std::string> commentdId);

    virtual ~Netizen(){}
    void getInfo();

    const std::string nickName()const;
    const std::vector<std::string> jottings() const;
    const std::vector<std::string> fans() const;
    const std::vector<std::string> concerneds() const;

    virtual nlohmann::json getAbstract() override;

private:
    std::string m_nickName;
    std::unordered_map<std::string, JottingProxy> _jottings;
    std::unordered_map<std::string, NetizenProxy> _fans;
    std::unordered_map<std::string, NetizenProxy> _concerneds;
    std::unordered_map<std::string, CommentProxy> _comments;
};

#endif // NETIZEN_H
