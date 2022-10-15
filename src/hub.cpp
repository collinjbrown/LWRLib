#include "hub.h"

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <corecrt_math_defines.h>

namespace LWRL
{
	std::vector<UTIL::Filter>::iterator Hub::FindFilter(std::string name)
	{
		std::vector<UTIL::Filter>::iterator iter = filters.begin();

		for (iter; iter < filters.end(); iter++) { if (iter->name == name) { return iter; } }

		std::cout << "No filter was found by the name: " + name + "." << std::endl;
		return iter;
	}

	void Hub::RemoveFilter(std::string name)
	{
		std::vector<UTIL::Filter>::iterator iter = FindFilter(name);

		if (iter != filters.end()) { filters.erase(iter); }
	}

	glm::vec3 Hub::GetAnchorPosition(ScreenAnchor anchor, glm::vec3 prospPosition)
	{
		if (anchor == ScreenAnchor::bottomLeft) return inputStates->cameraPosition - glm::vec3(width * inputStates->zoom / 2.0f, height * inputStates->zoom / 2.0f, 0.0f) + (prospPosition * inputStates->zoom);
		if (anchor == ScreenAnchor::topLeft) return inputStates->cameraPosition - glm::vec3(width * inputStates->zoom / 2.0f, -height * inputStates->zoom / 2.0f, 0.0f) + (prospPosition * inputStates->zoom);
		if (anchor == ScreenAnchor::bottomRight) return inputStates->cameraPosition + glm::vec3(width * inputStates->zoom / 2.0f, -height * inputStates->zoom / 2.0f, 0.0f) + (prospPosition * inputStates->zoom);
		if (anchor == ScreenAnchor::topRight) return inputStates->cameraPosition + glm::vec3(width * inputStates->zoom / 2.0f, height * inputStates->zoom / 2.0f, 0.0f) + (prospPosition * inputStates->zoom);
		if (anchor == ScreenAnchor::center) return inputStates->cameraPosition + (prospPosition * inputStates->zoom);
	}

	void Hub::RenderText(glm::vec3 position, glm::vec4 color, std::string text, Font* font, float scale, bool zoom)
	{
		if (zoom) textRenderer->RenderText(position, color, text, font, scale, inputStates->zoom);
		else textRenderer->RenderText(position, color, text, font, scale);
	}

	void Hub::RenderSprite(glm::vec3 pos, glm::vec4 color, Texture* texture)
	{
		int depthDifference = (((int)GetCameraPosition().z - 9) - (int)pos.z);

		if (pos.x + texture->GetWidth() >= windowLeft && pos.x - texture->GetWidth() <= windowRight &&
			pos.y + texture->GetHeight() >= windowBottom && pos.y - texture->GetHeight() <= windowTop &&
			depthDifference <= fadeDepth && depthDifference >= 0)
		{
			if (fadeDepth != 0 && depthDifference != 0) color = UTIL::ColorLerp(color, fadeColor, (depthDifference / (float)fadeDepth));
			for (int i = 0; i < filters.size(); i++) { color = UTIL::ColorLerp(color, filters[i].color, filters[i].strength); }

			spriteRenderer->RenderSprite(pos, color, texture);
		}
	}

	Texture* Hub::AddTexture(std::string file)
	{
		return spriteRenderer->AddTexture(file);
	}

	Font* Hub::AddFont(std::string file)
	{
		return textRenderer->AddFont(file);
	}

	void Hub::CheckFPS()
	{
		fpsCount++;

		float deltaTime = glfwGetTime() - lastTimeFPS;
		lastTimeFPS = glfwGetTime();

		sumTimeFPS += deltaTime;

		if (sumTimeFPS >= 1.0f)
		{
			fps = fpsCount;
			fpsCount = 0;
			sumTimeFPS = 0.0f;

			std::cout << "FPS: " + std::to_string(fps) << std::endl;
		}
	}

	float Hub::GetDeltaTime()
	{
		float dT = glfwGetTime() - lastTimeDT;
		lastTimeDT = glfwGetTime();
		return dT;
	}

	void Hub::UpdateBorders()
	{
		windowLeft = GetCameraPosition().x - ((width / 2.0f) * GetZoom());
		windowRight = GetCameraPosition().x + ((width / 2.0f) * GetZoom());
		windowBottom = GetCameraPosition().y - ((height / 2.0f) * GetZoom());
		windowTop = GetCameraPosition().y + ((height / 2.0f) * GetZoom());
	}

	bool Hub::Poll()
	{
		/*
			Poll() exists mostly as a middleman between the developer and glfw.
			As a principle, I want the developer to be able to talk solely with
			LWRLib without having to worry about what's going on in the
			background. Thus, Poll() removes the need for the developer to
			include this glfw call in their main's central while().
		*/

		return !glfwWindowShouldClose(window);
	}

	void Hub::Update()
	{
		/*
			Update() is meant to be called every frame.
			This is the third of the four functions I intend for the developer
			to need to use. It just clears the window, renders the scene, and
			swaps the buffers.
		*/

		float deltaTime = GetDeltaTime();

		CheckFPS();
		UpdateBorders();

		inputHandler->Update(inputSettings, inputStates, deltaTime);

		glm::vec3 cam = GetCameraPosition();
		glm::vec3 center = cam + glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		spriteRenderer->SetView(glm::lookAt(cam, center, up));

		spriteRenderer->UpdateProjection(width, height, inputStates->zoom, nearClip, farClip);

		glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
		glClear(GL_COLOR_BUFFER_BIT);

		spriteRenderer->Render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	void Hub::Terminate()
	{
		/*
			Terminate() is called on shutdown to ensure that everything
			closes down nice and neatly. It doesn't do much right now.
		*/

		spriteRenderer->Terminate();
		inputHandler->Terminate();

		delete inputSettings;
		delete inputStates;

		glfwTerminate();
		delete this;
	}

	Hub::Hub(int width, int height, std::string title)
	{
		// Here, we just make sure to copy over all the important variables.
		this->width = width;
		this->height = height;
		this->title = title;
		this->lastTimeFPS = glfwGetTime();
		this->lastTimeDT = glfwGetTime();

		// Now we init glfw and freak out if it doesn't work.
		if (!glfwInit())
		{
			std::cout << "Failed to initialize GLFW." << std::endl;
			return;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		glfwWindowHintString(GLFW_X11_CLASS_NAME, "OpenGL");
		glfwWindowHintString(GLFW_X11_INSTANCE_NAME, "OpenGL");

		// And finally we create the window (and make sure it all goes swimmingly).
		window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

		if (!window)
		{
			glfwTerminate();
			std::cout << "Failed to create Opengl Window." << std::endl;
			return;
		}

		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return;
		}

		// Enable blend.
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// And lastly prepare the renderer and input handler.
		spriteRenderer = new SpriteRenderer();
		textRenderer = new TextRenderer(spriteRenderer);

		inputHandler = new InputHandler(window);
		inputSettings = new InputSettings();
		inputStates = new InputStates();
	}
}
