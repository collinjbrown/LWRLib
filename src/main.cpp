// main.cpp
//

#include <iostream>
#include "lwrl.h"

int main(void)
{
    LWRL* lwrl = new LWRL(1280, 720, "test");

    while (lwrl->Poll())
    {
        lwrl->Update();
    }

    lwrl->Terminate();
}