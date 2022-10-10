// main.cpp
//

#include <iostream>
#include <filesystem>

#include "lwrl.h"

int main(void)
{
    LWRL* lwrl = new LWRL(1280, 720, "test");

    Texture* t0 = lwrl->AddTexture("assets/sprites/test.png");
    Texture* t1 = lwrl->AddTexture("assets/sprites/test2.png");

    srand(time(NULL));

    while (lwrl->Poll())
    {
        for (int x = 0; x < 100; x++)
        {
            for (int y = 0; y < 100; y++)
            {
                float r = 1.0f; // static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                float g = 1.0f; //  static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                float b = 1.0f; //  static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

                Texture* t = t0;
                // if (rand() % 100 > 50) t = t1;

                lwrl->RenderSprite(glm::vec3(x * t->GetWidth(), y * t->GetHeight(), 0), glm::vec4(r, g, b, 1.0), t);
            }
        }

        lwrl->Update();
    }

    lwrl->Terminate();
}