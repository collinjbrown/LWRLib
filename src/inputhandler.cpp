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

		if (!settings->discreteXY)
		{
			if (moveUp) states->cameraPosition.y += (settings->cameraSpeedXY * states->zoom) * deltaTime;
			else if (moveDown) states->cameraPosition.y -= (settings->cameraSpeedXY * states->zoom) * deltaTime;

			if (moveRight) states->cameraPosition.x += (settings->cameraSpeedXY * states->zoom) * deltaTime;
			else if (moveLeft) states->cameraPosition.x -= (settings->cameraSpeedXY * states->zoom) * deltaTime;
		}
		else
		{
			if (states->sumXYMoveTime >= settings->moveDelay)
			{
				states->sumXYMoveTime = 0.0f;

				if (moveUp) states->cameraPosition.y += settings->tileWidth;
				else if (moveDown) states->cameraPosition.y -= settings->tileWidth;

				if (moveRight) states->cameraPosition.x += settings->tileWidth;
				else if (moveLeft) states->cameraPosition.x -= settings->tileWidth;

				if (moveIn) states->cameraPosition.z -= 1;
				else if (moveOut) states->cameraPosition.z += 1;
			}
			else
			{
				states->cameraPosition.x = (int)(states->cameraPosition.x / settings->tileWidth) * settings->tileWidth;
				states->cameraPosition.y = (int)(states->cameraPosition.y / settings->tileWidth) * settings->tileWidth;
				states->sumXYMoveTime += deltaTime;
			}
		}

		if (!settings->discreteZ)
		{
			if (moveIn) states->cameraPosition.z -= (settings->cameraSpeedZ * states->zoom) * deltaTime;
			else if (moveOut) states->cameraPosition.z += (settings->cameraSpeedZ * states->zoom) * deltaTime;
		}
		else
		{
			if (states->sumZMoveTime >= settings->moveDelay)
			{
				states->sumZMoveTime = 0.0f;

				if (moveIn) states->cameraPosition.z -= 1;
				else if (moveOut) states->cameraPosition.z += 1;
			}
			else
			{
				states->cameraPosition.z = (int)states->cameraPosition.z;

				states->sumZMoveTime += deltaTime;
			}
		}

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