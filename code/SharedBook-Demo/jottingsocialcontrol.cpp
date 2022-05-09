#include "jottingbroker.h"
#include "materialbroker.h"
#include "commentbroker.h"
#include "netizenbroker.h"
#include "netizen.h"

#include "jottingsocialcontrol.h"

#include <iostream>
#include <fstream>
#include <sstream>

JottingSocialControl::JottingSocialControl(){
    this->nb = new NetizenBroker();
    this->jb = new JottingBroker();
    this->cb = new CommentBroker();
    this->mb = new MaterialBroker();

//    Init();

}

void JottingSocialControl::Init()
{
    std::cout<<"Init all Data........"<<"\n";

    //init Netizen
    std::ifstream fin;
    fin.open("/run/media/root/study/ShareBook/代码/SharedBook-Demo/netizenData.txt");
    std::string str;
    std::vector<Netizen> nts;
    int id;
    std::string nickname;
    std::string avater;
    std::string signal;

    while (getline(fin, str)){
        std::istringstream stream(str);
        stream>>id>>nickname>>avater>>signal;
//        std::cout<<"\n"<<id<<nickname<<avater<<signal<<std::endl;
        nts.push_back(Netizen(id,nickname,avater,signal));
    }
    fin.close();

    //init Material
    std::vector<Material> mtrs{
        Material(201,std::vector<std::string>{"pictures001","pictures002"}),
        Material(202,std::vector<std::string>{"pictures003"}),
        Material(203,std::vector<std::string>{"pictures004"}),
        Material(204,std::vector<std::string>{"pictures005"}),
        Material(205,std::vector<std::string>{"pictures006"}),
        Material(206,std::vector<std::string>{"pictures007"}),
        Material(207,std::vector<std::string>{"pictures008"}),
        Material(208,std::vector<std::string>{"pictures009"}),
        Material(209,std::vector<std::string>{"pictures010"}),
        Material(210,std::vector<std::string>{"pictures011"}),
        Material(211,std::vector<std::string>{"pictures012"}),
        Material(212,std::vector<std::string>{"pictures013"}),
        Material(213,std::vector<std::string>{"pictures014"}),
        Material(214,std::vector<std::string>{"pictures015"}),
    };

    //init Jotting
    std::ifstream finJot;
    finJot.open("/run/media/root/study/ShareBook/代码/SharedBook-Demo/jottingData.txt");
    std::string strJot;
    std::vector<Jotting> jts;
    int jotId;
    std::string time;
    std::string text;
    int netizenId;
    int materialId;

    while(getline(finJot,strJot)){
        std::istringstream stream(strJot);
        stream>>jotId>>time>>text>>netizenId>>materialId;
        jts.push_back(Jotting(jotId,time,text));
    }

    jts[0].setMaterial(new Material(mtrs[0]));
    jts[1].setMaterial(new Material(mtrs[0]));
    jts[2].setMaterial(new Material(mtrs[1]));
    jts[3].setMaterial(new Material(mtrs[2]));
    jts[4].setMaterial(new Material(mtrs[3]));
    jts[5].setMaterial(new Material(mtrs[4]));
    jts[6].setMaterial(new Material(mtrs[5]));
    jts[7].setMaterial(new Material(mtrs[6]));
    jts[8].setMaterial(new Material(mtrs[7]));
    jts[9].setMaterial(new Material(mtrs[8]));
    jts[10].setMaterial(new Material(mtrs[9]));
    jts[11].setMaterial(new Material(mtrs[10]));
    jts[12].setMaterial(new Material(mtrs[11]));
    jts[13].setMaterial(new Material(mtrs[12]));
    jts[14].setMaterial(new Material(mtrs[13]));

    jts[0].setPublisher(new Netizen(nts[0]));
    jts[1].setPublisher(new Netizen(nts[0]));
    jts[2].setPublisher(new Netizen(nts[0]));
    jts[3].setPublisher(new Netizen(nts[0]));
    jts[4].setPublisher(new Netizen(nts[1]));
    jts[5].setPublisher(new Netizen(nts[1]));
    jts[6].setPublisher(new Netizen(nts[1]));
    jts[7].setPublisher(new Netizen(nts[2]));
    jts[8].setPublisher(new Netizen(nts[2]));
    jts[9].setPublisher(new Netizen(nts[3]));
    jts[10].setPublisher(new Netizen(nts[3]));
    jts[11].setPublisher(new Netizen(nts[3]));
    jts[12].setPublisher(new Netizen(nts[3]));
    jts[13].setPublisher(new Netizen(nts[3]));
    jts[14].setPublisher(new Netizen(nts[4]));

/*
    while (getline(finJot, strJot)){
        std::istringstream stream(strJot);
        stream>>jotId>>time>>text>>netizenId>>materialId;
        std::cout<<"\n"<<jotId<<time<<text<<netizenId<<materialId<<std::endl;
        for(auto & nt:nts){
            for(auto & mtr:mtrs){
                if(materialId == mtr.getMaterialId() && netizenId == nt.getID()){
                    Jotting jot(jotId,time,text);
                    jot.setMaterial(&mtr);
                    jot.setPublisher(&nt);
                    jts.push_back(jot);

                }
            }
        jts.push_back(Jotting(jotId,time,text));
        }

    }
    finJot.close();*/

    nts[0].setFans(std::vector<Netizen>{nts[1],nts[2],nts[3]});
    nts[0].setInterests(std::vector<Netizen>{nts[4]});
    nts[0].setJottings(std::vector<Jotting>{jts[0],jts[1],jts[2],jts[3]});

    nts[1].setFans(std::vector<Netizen>{nts[3],nts[4]});
    nts[1].setInterests(std::vector<Netizen>{nts[0]});
    nts[1].setJottings(std::vector<Jotting>{jts[4],jts[5],jts[6]});

    nts[2].setFans(std::vector<Netizen>{nts[3]});
    nts[2].setInterests(std::vector<Netizen>{nts[0]});
    nts[2].setJottings(std::vector<Jotting>{jts[7],jts[8]});

    nts[3].setFans(std::vector<Netizen>{nts[4]});
    nts[3].setInterests(std::vector<Netizen>{nts[0],nts[1],nts[2]});
    nts[3].setJottings(std::vector<Jotting>{jts[9],jts[10],jts[11],jts[12],jts[13]});

    nts[4].setFans(std::vector<Netizen>{nts[0]});
    nts[4].setInterests(std::vector<Netizen>{nts[1]});
    nts[4].setJottings(std::vector<Jotting>{jts[14]});


    nb->setNetizens(nts);
    jb->setJottings(jts);
    mb->setMaterials(mtrs);

    /*
    //init Material
    std::ifstream finMtr;
    finMtr.open("../SharedBook-Demo/materialData.txt");
    std::string strMtr;
    std::vector<Material> mts;
    int mtrId;
    std::string picture;

    while (getline(finMtr, str)){
        std::istringstream stream(str);
        stream>>mtrId>>picture;

        std::cout<<"\n"<<mtrId<<picture<<std::endl;

    }
    finMtr.close();*/

    std::cout<<"Init Finish!!"<<std::endl;
}

void JottingSocialControl::login(int id)
{
    //The controller finds netize's all information according to netizen acount.
    m_netizen = nb->findNetizenByID(id);
    m_netizen->get_Netizen_ID_Info();

    //Concurrent operation
    //According to the ID information of netizens, find the Jottings published by netizens
    //from the JottingBroker,and set them to the Netizen class.
    //get the degist of all jottings.

    //A:
    m_netizen->setJottings( jb->find_Netizen_Jottings(m_netizen->getID()));
    m_netizen->getAllJotDig(nb,mb);

    //According to the ID of the netizen, find the fans and interests
    //of the netizen through the NetizenBroker.

    //B:
    m_netizen->setFans(nb->findFansByID(m_netizen->getID()));
    m_netizen->get_Fans_ID_Info();

    //C:
    m_netizen->setInterests(nb->findInterestsByID(m_netizen->getID()));
    m_netizen->get_Interests_ID_Info();

}

void JottingSocialControl::pushJottings()
{
    //Concurrent operation
    //A: Find Jottings published by netizen's interests and push them
    m_netizen->pushInterestsJotting(nb,jb,mb);

    //B:Find the Jottings published in the system and push them randomly
    m_jottings = jb->findSomeJottings();

    for(auto jotting: m_jottings){
        jotting.getJotDig(nb,mb);
    }
}


