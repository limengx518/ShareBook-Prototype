//#include <iostream>
#include "relationalbroker.h"
#include "netizenbroker.h"
#include "jottingbroker.h"
#include "jottingsocialcontrol.h"
#include "messagesequence.h"

using namespace std;

#include <unordered_set>

int main()
{
//        JottingBroker * broker=JottingBroker::getInstance();
//        broker->initDataBase();

    JottingSocialControl control;

    cout<<"\n========网民登录=========\n"<<endl;
    cout<<control.login("3703570432").dump(4)<<endl;
    /*
    cout<<"\n========推送笔记=========\n"<<endl;
    cout<<control.pushJottings("3695181824").dump(4)<<endl;
    cout<<"\n========详情查看某一笔记=========\n"<<endl;
    cout<<control.checkOneJotting("3695181824","3405774848").dump(4)<<endl;
    */

    /*cout<<"\n========发布笔记=========\n"<<endl;
    cout<<control.publishJotting("3699376128","今天天气不错")<<endl;
    */

    MessageSequence::getInstance()->updateMessageQueue();
    cout<<"\n========浏览消息=========\n"<<endl;
    cout<<control.scanMessage("3703570432").dump(4)<<endl;
    cout<<"\n========查看消息详情内容=========\n"<<endl;
    cout<<control.checkMessage("3703570432","1862270976").dump(4)<<endl;
    MessageSequence::getInstance()->updateMessageQueue();


//    control.addComment("1","1","hahahah");

    return 0;
}
