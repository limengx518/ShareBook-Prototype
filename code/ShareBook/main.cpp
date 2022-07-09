//#include <iostream>
#include "relationalbroker.h"
#include "materialbroker.h"
#include "netizenbroker.h"
#include "jottingbroker.h"
#include "jottingsocialcontrol.h"
#include "messagesequence.h"
#include <unordered_set>
#include "commentbroker.h"

using namespace std;

int main()
{
//    JottingBroker::getInstance()->initDataBase();
    JottingSocialControl control;

    cout<<"\n========网民登录=========\n"<<endl;
    cout<<control.login("10").dump(4)<<endl;

    cout<<"\n========推送笔记=========\n"<<endl;
    cout<<control.pushJottings("3695181824").dump(4)<<endl;
    cout<<"\n========详情查看某一笔记=========\n"<<endl;
    cout<<control.checkOneJotting("3695181824","3405774848").dump(4)<<endl;


    cout<<"\n========发布笔记=========\n"<<endl;
    nlohmann::json jotting;
    jotting["content"]="今天天气不错";
    jotting["materials"]={"path_new1","path_new2"};
    cout<<control.publishJotting("3699376128",jotting)<<endl;

    control.comment("3695181824","3405774848","hahahah");

    cout<<"\n========关注=========\n"<<endl;
    control.follow("9","10");

    getchar();

    cout<<"\n========浏览消息=========\n"<<endl;
    cout<<control.scanMessage("3703570432").dump(4)<<endl;
    cout<<"\n========查看消息详情内容=========\n"<<endl;
    cout<<control.checkMessage("3703570432","1862270976").dump(4)<<endl;


    return 0;
}


