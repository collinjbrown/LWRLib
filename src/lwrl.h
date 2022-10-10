/*
	Desc:	The real meat and potatoes of LWRLib—this is what the user will instantiate and call
			in order to interface with the library.
*/

#ifndef LWRL_H
#define LWRL_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>

#include "external/check_error.h"
#include "renderer.h"

class LWRL
{
private:
	GLFWwindow*		window;
	int				width;
	int				height;
	std::string		title;

	unsigned int	fps = 0;
	unsigned int	fpsCount = 0;
	float			lastTime;
	float			sumTime = 0.0f;

	glm::vec2		mousePosition = glm::vec2(0.0f, 0.0f);
	glm::vec3		cameraPosition = glm::vec3(1600.0f, 1600.0f, 10.0f);

	float			zoom = 2.0f;
	float			zoomSpeed = 1.0f;
	float			cameraSpeed = 80.0f;

	float nearClip = 0.1f;
	float farClip = 15000.0f;

	Renderer*		renderer;

public:
	int GetWidth() { return width; }
	int GetHeight() { return height; }
	std::string GetTitle() { return title; }

	void SetWidth(int width) { this->width = width; }
	void SetHeight(int height) { this->height = height; }
	void SetTitle(std::string title) { this->title = title; }

	void RenderSprite(glm::vec3 pos, glm::vec4 color, Texture* texture);
	Texture* AddTexture(std::string file);

	void CheckFPS();

	bool Poll();
	void Update();
	void Terminate();
	LWRL(int width, int height, std::string title);
};

#endif