// main.cpp
//

#include <iostream>
#include "lwrl.h"

int main(void)
{
    LWRL* lwrl = new LWRL(1280, 720, "test");

    Texture* t = lwrl->AddTexture("assets/sprites/block.png");

    while (lwrl->Poll())
    {
        lwrl->RenderSprite(glm::vec3(0, 0, 0), glm::vec4(1.0, 1.0, 1.0, 1.0), t);
        lwrl->Update();
    }

    lwrl->Terminate();
}