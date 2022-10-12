#include "inputhandler.h"

namespace LWRL
{
	void InputHandler::Update(InputSettings* settings, InputStates* states, float deltaTime)
	{
		bool moveUp = (glfwGetKey(window, moveUpKey) == GLFW_PRESS);
		bool moveDown = ((glfwGetKey(window, moveDownKey) == GLFW_PRESS) && !moveUp);
		bool moveLeft = (glfwGetKey(window, moveLeftKey) == GLFW_PRESS);
		bool moveRight = ((glfwGetKey(window, moveRightKey) == GLFW_PRESS) && !moveLeft);
		bool moveIn = (glfwGetKey(window, moveInKey) == GLFW_PRESS);
		bool moveOut = ((glfwGetKey(window, moveOutKey) == GLFW_PRESS) && !moveIn);
		bool zoomIn = (glfwGetKey(window, zoomInKey) == GLFW_PRESS);
		bool zoomOut = ((glfwGetKey(window, zoomOutKey) == GLFW_PRESS) && !zoomIn);

		if (moveUp) states->cameraPosition.y += (settings->cameraSpeedXY * states->zoom) * deltaTime;
		else if (moveDown) states->cameraPosition.y -= (settings->cameraSpeedXY * states->zoom) * deltaTime;

		if (moveRight) states->cameraPosition.x += (settings->cameraSpeedXY * states->zoom) * deltaTime;
		else if (moveLeft) states->cameraPosition.x -= (settings->cameraSpeedXY * states->zoom) * deltaTime;

		if (moveIn) states->cameraPosition.z -= (settings->cameraSpeedZ * states->zoom) * deltaTime;
		else if (moveOut) states->cameraPosition.z += (settings->cameraSpeedZ * states->zoom) * deltaTime;

		if (zoomIn) states->zoom -= settings->zoomSpeed * deltaTime;
		else if (zoomOut) states->zoom += settings->zoomSpeed * deltaTime;

		if (states->zoom < settings->minZoom) states->zoom = settings->minZoom;
		else if (states->zoom > settings->maxZoom) states->zoom = settings->maxZoom;
	}

	void InputHandler::Terminate()
	{
		// Do anything you need to do before shutting down.
		delete this;
	}


	InputHandler::InputHandler(GLFWwindow* window)
	{
		this->window = window;
	}
}