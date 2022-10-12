// main.cpp
//

#include <iostream>
#include <filesystem>

#include "hub.h"

int main(void)
{
    LWRL::Hub* lwrl = new LWRL::Hub(1280, 720, "test");

    LWRL::Texture* t0 = lwrl->AddTexture("assets/sprites/test.png");
    LWRL::Texture* t1 = lwrl->AddTexture("assets/sprites/test2.png");

    // srand(time(NULL));

    // lwrl->AddFilter("red", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), 0.5f);

    while (lwrl->Poll())
    {
        for (int x = 0; x < 32; x++)
        {
            for (int y = 0; y < 32; y++)
            {
                lwrl->RenderSprite(glm::vec3(x * t0->GetWidth(), y * t0->GetWidth(), -y), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), t0);
            }
        }

        lwrl->Update();
    }

    lwrl->Terminate();
}