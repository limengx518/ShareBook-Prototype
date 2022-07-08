#include <iostream>
#include "relationalbroker.h"
#include "materialbroker.h"
#include "netizenbroker.h"
#include "jottingbroker.h"
#include "jottingsocialcontrol.h"
#include "commentbroker.h"
#include <thread>

using namespace std;

int main()
{
    JottingSocialControl control{};
    cout<<control.login("10")<<endl;

    getchar();


    return 0;
}


