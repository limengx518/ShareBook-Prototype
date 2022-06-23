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

    sql::ResultSet* query(std::string command);
    void insert(std::string command);

    virtual void update()=0;

    virtual ~RelationalBroker(){}
private:
    std::unique_ptr<sql::Connection> m_connection;
};

#endif // RELATIONALBROKER_H
