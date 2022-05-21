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

        //创造表
        std::unique_ptr<sql::PreparedStatement> stmnt(m_connection->prepareStatement("create table if not exists Netizen(N_id INT(15) unsigned AUTO_INCREMENT,N_nickName varchar(20) not null,primary key(N_id))"));
        stmnt->executeQuery();

        std::unique_ptr<sql::PreparedStatement> stmnt2(m_connection->prepareStatement("create table if not exists Jotting (J_id INT(15) unsigned NOT NULL ,J_content varchar(2000) not null,N_id INT(15) unsigned not null,primary key(J_id),foreign key(N_id) references Netizen(N_id) on delete cascade on update cascade)"));
        stmnt2->executeQuery();


        std::unique_ptr<sql::PreparedStatement> stmnt3(m_connection->prepareStatement("create table if not exists Material (M_id INT(15) unsigned NOT NULL ,M_path varchar(100) not null,J_id INT(15) unsigned not null,primary key(M_id),foreign key(J_id) references Jotting(J_id) on delete cascade on update cascade)"));
        stmnt3->executeQuery();


        std::unique_ptr<sql::PreparedStatement> stmnt4(m_connection->prepareStatement("create table if not exists Relation (R_id INT(15) unsigned NOT NULL,N_Fan_id INT(15) unsigned NOT NULL,primary key (R_id,N_Fan_id),foreign key(R_id) references Netizen(N_id) on delete cascade on update cascade,foreign key(N_Fan_id) references Netizen(N_id) on delete cascade on update cascade)"));
        stmnt4->executeQuery();

        std::unique_ptr<sql::PreparedStatement> stmnt7(m_connection->prepareStatement("insert into Netizen (N_id,N_nickName) values(?,?)"));
        stmnt7->setInt(1,1);
        stmnt7->setString(2,"rose");
        stmnt7->execute();

        stmnt7->setInt(1,2);
        stmnt7->setString(2,"Monica");
        stmnt7->execute();

        stmnt7->setInt(1,3);
        stmnt7->setString(2,"Phoebe");
        stmnt7->execute();

        stmnt7->setInt(1,4);
        stmnt7->setString(2,"Joey");
        stmnt7->execute();

        std::unique_ptr<sql::PreparedStatement> stmnt8(m_connection->prepareStatement("insert into Jotting (J_id,J_content,N_id) values(?,?,?)"));

        stmnt8->setInt(1,1);
        stmnt8->setString(2,"wind wind flower");
        stmnt8->setInt(3,1);
        stmnt8->execute();

        stmnt8->setInt(1,2);
        stmnt8->setString(2,"Turn it up now hear me");
        stmnt8->setInt(3,2);
        stmnt8->execute();

        std::unique_ptr<sql::PreparedStatement> stmnt6(m_connection->prepareStatement("insert into Material (M_id,M_path,J_id) values(?,?,?)"));

        stmnt6->setInt(1,1);
        stmnt6->setString(2,"picturePath1");
        stmnt6->setInt(3,1);
        stmnt6->execute();

        stmnt6->setInt(1,2);
        stmnt6->setString(2,"videoPath1");
        stmnt6->setInt(3,2);
        stmnt6->execute();

        std::unique_ptr<sql::PreparedStatement> stmnt5(m_connection->prepareStatement("insert into Relation (R_id,N_Fan_id) values(?,?)"));

        stmnt5->setInt(1,1);
        stmnt5->setInt(2,3);
        stmnt5->execute();

        stmnt5->setInt(1,2);
        stmnt5->setInt(2,1);
        stmnt5->execute();

        stmnt5->setInt(1,4);
        stmnt5->setInt(2,1);
        stmnt5->execute();

    }catch(sql::SQLException& e){
        std::cerr<< e.what() << std::endl;
    }
}

sql::ResultSet* RelationalBroker::query(std::string command)
{
    try {
            // Create a new Statement
        std::unique_ptr<sql::Statement> stmnt(m_connection->createStatement());
            // Execute query
        sql::ResultSet *res = stmnt->executeQuery(command);
        return res;

    }catch(sql::SQLException& e){
        std::cerr << "Error selecting tasks: " << e.what() << std::endl;
    }
    return nullptr;
}




