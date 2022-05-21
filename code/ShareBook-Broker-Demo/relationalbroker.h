#ifndef RELATIONALBROKER_H
#define RELATIONALBROKER_H
#include <mariadb/conncpp.hpp>

class Jotting;
class Netizen;
class Material;

class RelationalBroker
{
public:
    RelationalBroker();
    void initDataBase();
    virtual ~RelationalBroker(){}

    sql::ResultSet* query(std::string command);

private:
    std::unique_ptr<sql::Connection> m_connection;

};

#endif // RELATIONALBROKER_H
