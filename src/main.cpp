// main.cpp
//

#include <iostream>
#include <filesystem>

#include "lwrl.h"

int main(void)
{
    LWRL* lwrl = new LWRL(1280, 720, "test");

    Texture* t = lwrl->AddTexture("assets/sprites/test.png");

    srand(time(NULL));

    while (lwrl->Poll())
    {
        for (int x = 0; x < 100; x++)
        {
            for (int y = 0; y < 100; y++)
            {
                float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

                lwrl->RenderSprite(glm::vec3(x * t->GetWidth(), y * t->GetHeight(), 0), glm::vec4(r, g, b, 1.0), t);
            }
        }

        lwrl->Update();
    }

    lwrl->Terminate();
}