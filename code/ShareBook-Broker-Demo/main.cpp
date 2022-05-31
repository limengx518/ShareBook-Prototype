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
    JottingSocialControl control("1");
//    Cache cache;
    return 0;
}
