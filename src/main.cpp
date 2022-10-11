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

    srand(time(NULL));

    while (lwrl->Poll())
    {
        for (int x = 0; x < 32; x++)
        {
            for (int y = 0; y < 32; y++)
            {
                for (int z = 0; z < 32; z++)
                {
                    // LWRL::Texture* t = t0;
                    // if (rand() % 100 > 50) t = t1;

                    /*float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                    float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                    float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);*/

                    lwrl->RenderSprite(glm::vec3(x * t0->GetWidth(), y * t0->GetWidth(), -z), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), t0);
                }
            }
        }

        lwrl->Update();
    }

    lwrl->Terminate();
}