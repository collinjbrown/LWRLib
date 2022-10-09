#include "lwrl.h"

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <corecrt_math_defines.h>

void LWRL::RenderSprite(glm::vec3 pos, glm::vec4 color, Texture* texture)
{
	renderer->RenderSprite(pos, color, texture);
}

Texture* LWRL::AddTexture(std::string file)
{
	return renderer->AddTexture(file);
}

bool LWRL::Poll()
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

void LWRL::Update()
{
	/*
		Update() is meant to be called every frame.
		This is the third of the four functions I intend for the developer
		to need to use. It just clears the window, renders the scene, and
		swaps the buffers.
	*/

	glm::vec3 cam = glm::vec3(cameraPosition.x, cameraPosition.y, cameraPosition.z);
	glm::vec3 center = cam + glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	renderer->SetView(glm::lookAt(cam, center, up));

	renderer->UpdateProjection(width, height, zoom, nearClip, farClip);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	renderer->Render();

	glfwSwapBuffers(window);
	glfwPollEvents();
	glCheckError();
}

void LWRL::Terminate()
{
	/*
		Terminate() is called on shutdown to ensure that everything
		closes down nice and neatly. It doesn't do much right now.
	*/

	renderer->Terminate();
	glfwTerminate();
	delete this;
}

LWRL::LWRL(int width, int height, std::string title)
{
	// Here, we just make sure to copy over all the important variables.
	this->width = width;
	this->height = height;
	this->title = title;

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

	// And lastly prepare the renderer.
	renderer = new Renderer();
}
