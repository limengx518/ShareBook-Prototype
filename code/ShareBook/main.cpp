//#include <iostream>
#include "relationalbroker.h"
#include "netizenbroker.h"
#include "jottingbroker.h"
#include "jottingsocialcontrol.h"

using namespace std;

#include <unordered_set>

int main()
{
//        JottingBroker * broker=JottingBroker::getInstance();
//        broker->initDataBase();

    JottingSocialControl control;

    /*
    cout<<"\n========网民登录=========\n"<<endl;
    cout<<control.login("3695181824").dump(4)<<endl;
    cout<<"\n========推送笔记=========\n"<<endl;
    cout<<control.pushJottings("3695181824").dump(4)<<endl;
    cout<<"\n========详情查看某一笔记=========\n"<<endl;
    cout<<control.checkOneJotting("3695181824","3405774848").dump(4)<<endl;
    */

    cout<<"\n========发布笔记=========\n"<<endl;
    cout<<control.publishJotting("3699376128","今天天气不错")<<endl;


//    control.addComment("1","1","hahahah");

    return 0;
}
