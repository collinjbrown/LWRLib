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
        for (int x = 0; x < 100; x++)
        {
            for (int y = 0; y < 100; y++)
            {
                LWRL::Texture* t = t0;
                // if (rand() % 100 > 50) t = t1;

                float tX = x * t->GetWidth();
                float tY = y * t->GetWidth();
                float r = 1.0f; // static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                float g = 1.0f; //  static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                float b = 1.0f; //  static_cast <float> (rand()) / static_cast <float> (RAND_MAX);


                lwrl->RenderSprite(glm::vec3(tX, tY, 0), glm::vec4(r, g, b, 1.0), t);

            }
        }

        lwrl->Update();
    }

    lwrl->Terminate();
}