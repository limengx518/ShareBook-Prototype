#include "relationalbroker.h"
#include "netizen.h"
#include <iostream>
#include "jotting.h"
#include "material.h"
#include <string>

RelationalBroker::RelationalBroker()
{
    // Instantiate Driver
    sql::Driver* driver = sql::mariadb::get_driver_instance();

    // Configure Connection
    sql::SQLString url("jdbc:mariadb://localhost:3306/ShareBook");
    sql::Properties properties({{"user", "root"}, {"password", "root"}});

    // Establish Connection
    std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));
    m_connection=std::move(conn);

}

void RelationalBroker::initDataBase()
{
    try {
//        std::unique_ptr<sql::PreparedStatement> stmnt(m_connection->prepareStatement("create table Netizen (N_id INT(11) unsigned NOT NULL AUTO_INCREMENT,N_nickName varchar(20) not null,primary key(N_id))"));
//        stmnt->executeQuery();
//        std::unique_ptr<sql::PreparedStatement> stmnt2(m_connection->prepareStatement("create table Jotting (J_id INT(11) unsigned NOT NULL AUTO_INCREMENT,J_content varchar(2000) not null,N_id INT(11) unsigned not null,primary key(J_id),foreign key(N_id) references Netizen(N_id) on delete cascade on update cascade)"));
//        stmnt2->executeQuery();
//        std::unique_ptr<sql::PreparedStatement> stmnt2(m_connection->prepareStatement("create table Material (M_id INT(11) unsigned NOT NULL AUTO_INCREMENT,M_path varchar(100) not null,J_id INT(11) unsigned not null,primary key(M_id),foreign key(J_id) references Jotting(J_id) on delete cascade on update cascade)"));
//        stmnt2->executeQuery();
//        std::unique_ptr<sql::PreparedStatement> stmnt2(m_connection->prepareStatement("create table Relation (R_id INT(11) unsigned NOT NULL,N_Fan_id INT(11) unsigned NOT NULL,primary key (R_id,N_Fan_id),foreign key(R_id) references Netizen(N_id) on delete cascade on update cascade,foreign key(N_Fan_id) references Netizen(N_id) on delete cascade on update cascade)"));
//        stmnt2->executeQuery();
//        std::unique_ptr<sql::PreparedStatement> stmnt(m_connection->prepareStatement("insert into Relation (R_id,N_Fan_id) values(2,1)"));
//        stmnt->executeQuery();
//        std::unique_ptr<sql::PreparedStatement> stmnt1(m_connection->prepareStatement("insert into Relation (R_id,N_Fan_id) values(1,3)"));
//        stmnt1->executeQuery();
        std::unique_ptr<sql::PreparedStatement> stmnt3(m_connection->prepareStatement("insert into Relation (R_id,N_Fan_id) values(4,1)"));
        stmnt3->executeQuery();
    }catch(sql::SQLException& e){
        std::cerr << "Error inserting new task: " << e.what() << std::endl;
    }
}

Jotting *RelationalBroker::findJottingById(std::string jottingId)
{
    std::string com="select * from Jotting where J_id="+jottingId;
    Jotting *jotting=nullptr;
    try {
            // Create a new Statement
        std::unique_ptr<sql::Statement> stmnt(m_connection->createStatement());
            // Execute query
        sql::ResultSet *res = stmnt->executeQuery(com);

        std::string id,content;
            // Loop through and print results
        while (res->next()) {
            id=std::to_string(res->getInt(1));
            content=res->getString(2);
        }
        jotting=new Jotting(id,content,findJottingMaterial(id));
    }catch(sql::SQLException& e){
        std::cerr << "Error selecting tasks: " << e.what() << std::endl;
    }
    return jotting;
}

Netizen *RelationalBroker::findNetizenById(std::string netizenId)
{
    std::string com="select * from Netizen where N_id="+netizenId;
    Netizen *netizen=nullptr;
    try {
            // Create a new Statement
        std::unique_ptr<sql::Statement> stmnt(m_connection->createStatement());
            // Execute query
        sql::ResultSet *res = stmnt->executeQuery(com);

        std::string id,nickName;
            // Loop through and print results
        while (res->next()) {
            id=std::to_string(res->getInt(1));
            nickName=res->getString(2);
        }

        netizen=new Netizen(id,nickName,findNetizenJotting(id),findNetizenFans(id),findNetizenConcereds(id));
    }catch(sql::SQLException& e){
        std::cerr << "Error selecting tasks: " << e.what() << std::endl;
    }
    return netizen;
}

Material *RelationalBroker::findMaterialById(std::string materialId)
{
    std::string com="select * from Material where J_id="+materialId;
    Material *material=nullptr;
    try {
            // Create a new Statement
        std::unique_ptr<sql::Statement> stmnt(m_connection->createStatement());
            // Execute query
        sql::ResultSet *res = stmnt->executeQuery(com);

        std::string id,path;
            // Loop through and print results
        while (res->next()) {
            id=std::to_string(res->getInt(1));
            path=res->getString(2);
        }

        material=new Material(id,path);
    }catch(sql::SQLException& e){
        std::cerr << "Error selecting tasks: " << e.what() << std::endl;
    }
    return material;
}

std::vector<std::string> RelationalBroker::findNetizenJotting(std::string netizenId)
{
    std::string com="select J_id from Jotting where N_id="+netizenId;
    std::vector<std::string> jottingIds;
    try {
            // Create a new Statement
        std::unique_ptr<sql::Statement> stmnt(m_connection->createStatement());
            // Execute query
        sql::ResultSet *res = stmnt->executeQuery(com);
            // Loop through and print results
        while (res->next()) {
            jottingIds.push_back(std::to_string(res->getInt(1)));
        }
    }catch(sql::SQLException& e){
        std::cerr << "Error selecting tasks: " << e.what() << std::endl;
    }
    return jottingIds;
}

std::vector<std::string> RelationalBroker::findJottingMaterial(std::string jottingId)
{
    std::string com="select M_id from Material where J_id="+jottingId;
    std::vector<std::string> materialIds;
    try {
            // Create a new Statement
        std::unique_ptr<sql::Statement> stmnt(m_connection->createStatement());
            // Execute query
        sql::ResultSet *res = stmnt->executeQuery(com);

            // Loop through and print results
        while (res->next()) {
            materialIds.push_back(std::to_string(res->getInt(1)));
        }
    }catch(sql::SQLException& e){
        std::cerr << "Error selecting tasks: " << e.what() << std::endl;
    }
    return materialIds;
}

std::vector<std::string> RelationalBroker::findNetizenFans(std::string netizenId)
{
    std::string com="select N_Fan_id from Relation where R_id="+netizenId;
    std::vector<std::string> fansIds;
    try {
            // Create a new Statement
        std::unique_ptr<sql::Statement> stmnt(m_connection->createStatement());
            // Execute query
        sql::ResultSet *res = stmnt->executeQuery(com);

            // Loop through and print results
        while (res->next()) {
            fansIds.push_back(std::to_string(res->getInt(1)));
        }
    }catch(sql::SQLException& e){
        std::cerr << "Error selecting tasks: " << e.what() << std::endl;
    }
    return fansIds;
}

std::vector<std::string> RelationalBroker::findNetizenConcereds(std::string netizenId)
{
    std::string com="select R_id from Relation where N_Fan_id="+netizenId;
    std::vector<std::string> conceredIds;
    try {
            // Create a new Statement
        std::unique_ptr<sql::Statement> stmnt(m_connection->createStatement());
            // Execute query
        sql::ResultSet *res = stmnt->executeQuery(com);

            // Loop through and print results
        while (res->next()) {
            conceredIds.push_back(std::to_string(res->getInt(1)));
        }
    }catch(sql::SQLException& e){
        std::cerr << "Error selecting tasks: " << e.what() << std::endl;
    }
    return conceredIds;
}
