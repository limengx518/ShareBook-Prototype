#include <iostream>
#include "jottingsocialcontrol.h"
using namespace std;

void initialize(){
}

int main()
{

    JottingSocialControl *jsc = new JottingSocialControl();
    int acount = 1;
    jsc->Init();

    jsc->login(1);
//    jsc->pushJottings();

    return 0;
}
