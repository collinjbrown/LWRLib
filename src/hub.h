/*
	Desc:	The interface of LWRLib�this is what the user will instantiate and call
			in order to interact with the library.
*/

#ifndef HUB_H
#define HUB_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <map>

#include "util.h"
#include "textrenderer.h"
#include "inputhandler.h"

namespace LWRL
{
	class Hub
	{
	private:
		int					test = 0;
		GLFWwindow*			window;
		unsigned int		width;
		unsigned int		height;
		std::string			title;

		unsigned int		fps = 0;
		unsigned int		fpsCount = 0;
		float				lastTimeFPS;
		float				sumTimeFPS = 0.0f;

		float				lastTimeDT;

		InputSettings*		inputSettings;
		InputStates*		inputStates;

		float				windowLeft = 0.0f;
		float				windowRight = 0.0f;
		float				windowTop = 0.0f;
		float				windowBottom = 0.0f;

		float				nearClip = 0.1f;
		float				farClip = 15000.0f;

		unsigned int		fadeDepth = 10;
		glm::vec4			fadeColor = glm::vec4(0.5f, 0.5f, 0.5f, 0.1f);


		std::vector<UTIL::Filter>		filters;
		SpriteRenderer*					spriteRenderer;
		InputHandler*					inputHandler;

		void CheckFPS();
		float GetDeltaTime();
		void UpdateBorders();

	public:
		int GetWidth() { return width; }
		int GetHeight() { return height; }
		std::string GetTitle() { return title; }
		
		void SetWidth(int width) { this->width = width; }
		void SetHeight(int height) { this->height = height; }
		void SetTitle(std::string title) { this->title = title; }

		float GetZoom() { return inputStates->zoom; }
		glm::vec3 GetCameraPosition() { return inputStates->cameraPosition; }

		glm::vec4 GetWindowBorders() { return glm::vec4(windowLeft, windowRight, windowTop, windowBottom); }

		void RenderSprite(glm::vec3 pos, glm::vec4 color, Texture* texture);
		Texture* AddTexture(std::string file);

		void AddFilter(std::string name, glm::vec4 filter, float strength) { filters.push_back({ name, filter, strength }); }
		std::vector<UTIL::Filter>::iterator FindFilter(std::string name);
		void RemoveFilter(std::string name);

		bool Poll();
		void Update();
		void Terminate();
		Hub(int width, int height, std::string title);
	};
}

#endif