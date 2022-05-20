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

    Jotting* findJottingById(std::string jottingId);
    Netizen* findNetizenById(std::string netizenId);
    Material* findMaterialById(std::string materialId);

    std::vector<std::string> findNetizenJotting(std::string netizenId);
    std::vector<std::string> findJottingMaterial(std::string jottingId);
    std::vector<std::string> findNetizenFans(std::string netizenId);
    std::vector<std::string> findNetizenConcereds(std::string netizenId);
    std::vector<Jotting *> findSomeJottings(std::string lastTime,std::string thisTime);

private:
    std::unique_ptr<sql::Connection> m_connection;

};

#endif // RELATIONALBROKER_H
