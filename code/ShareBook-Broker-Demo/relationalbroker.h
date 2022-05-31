#ifndef RELATIONALBROKER_H
#define RELATIONALBROKER_H
#include <mariadb/conncpp.hpp>
#include "cache.h"

class Jotting;
class Netizen;
class Material;


class RelationalBroker
{
public:
    RelationalBroker();

    void initDataBase();

    sql::ResultSet* query(std::string command);

    std::unordered_map<std::string,std::string> inCache(std::string objectId);
    void storeObject(std::string key,std::unordered_map<std::string,std::string> map);

    virtual ~RelationalBroker(){}
private:
    std::unique_ptr<sql::Connection> m_connection;
    Cache m_cache;
};

#endif // RELATIONALBROKER_H
