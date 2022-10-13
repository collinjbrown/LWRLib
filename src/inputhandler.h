#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

namespace LWRL
{
	struct InputStates
	{
		glm::vec2			mousePosition = glm::vec2(0.0f, 0.0f);
		glm::vec3			cameraPosition = glm::vec3(512.0f, 512.0f, 10.0f);

		float				zoom = 1.5f;

		float				sumMoveTime = 0.0f;
	};

	struct InputSettings
	{
		bool				discreteMovement = true;
		int					tileWidth = 32;
		float				moveDelay = 0.1f;

		float				cameraSpeedXY = 500.0f;
		float				cameraSpeedZ = 10.0f;
		float				minZoom = 0.1f;
		float				maxZoom = 2.0f;
		float				zoomSpeed = 0.8f;
	};

	class InputHandler
	{
	private:
		GLFWwindow* window;

		int moveUpKey = GLFW_KEY_W;
		int moveDownKey = GLFW_KEY_S;
		int moveRightKey = GLFW_KEY_D;
		int moveLeftKey = GLFW_KEY_A;
		int moveInKey = GLFW_KEY_E;
		int moveOutKey = GLFW_KEY_Q;

		int zoomInKey = GLFW_KEY_KP_ADD;
		int zoomOutKey = GLFW_KEY_KP_SUBTRACT;

	public:
		void Update(InputSettings* settings, InputStates* states, float deltaTime);
		void Terminate();

		InputHandler(GLFWwindow* window);
	};
}

#endif