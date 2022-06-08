#include <iostream>
#include "relationalbroker.h"
#include "netizenbroker.h"
#include "jottingbroker.h"
#include "jottingsocialcontrol.h"
#include "cache.h"
#include <sw/redis++/redis++.h>
using namespace std;


int main()
{
//        JottingBroker * broker=JottingBroker::getInstance();
//        broker->initDataBase();

    JottingSocialControl control;
    cout<<control.login("1").dump(4)<<endl;
    cout<<control.pushJottings("1").dump(4)<<endl;
    cout<<control.checkOneJotting("1","2").dump(4)<<endl;
//    control.pushJottings("2022-4-22 10:00:01","2022-7-22 10:00:03");
//    control.checkOneJotting("3");
//    control.addComment("1","1","hahahah");

    return 0;
}
