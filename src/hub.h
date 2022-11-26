/*
	Desc:	The interface of LWRLib—this is what the user will instantiate and call
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

		int					camZOffset = -9;
		unsigned int		fadeDepth = 5;
		glm::vec4			fadeColor = glm::vec4(0.5f, 0.5f, 0.5f, 0.1f);
		glm::vec4			backgroundColor = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);

		std::vector<UTIL::Filter>		filters;
		SpriteRenderer*					spriteRenderer;
		TextRenderer*					textRenderer;
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
		glm::vec3 GetAnchorPosition(ScreenAnchor anchor, glm::vec3 prospPosition);

		int GetCamZOffset() { return camZOffset; }
		void SetCamZOffset(int z) { this->camZOffset = z; }

		unsigned int GetFadeDepth() { return fadeDepth; }
		void SetFadeDepth(unsigned int fadeDepth) { this->fadeDepth = fadeDepth; }

		glm::vec4 GetWindowBorders() { return glm::vec4(windowLeft, windowRight, windowTop, windowBottom); }

		Quad GenerateQuad(glm::vec3 pos, glm::vec4 color, Texture* texture);
		void RenderQuad(Quad quad, Texture* texture);

		void RenderText(glm::vec3 position, glm::vec4 color, std::string text, Font* font, float scale, bool zoom);
		void RenderSprite(glm::vec3 pos, glm::vec4 color, Texture* texture);

		Texture* AddTexture(std::string file);
		Font* AddFont(std::string file);

		void AddFilter(std::string name, glm::vec4 filter, float strength) { filters.push_back({ name, filter, strength }); }
		std::vector<UTIL::Filter>::iterator FindFilter(std::string name);
		void RemoveFilter(std::string name);

		bool Poll();
		void HandleInputs();
		void Update();
		void Terminate();
		Hub(int width, int height, std::string title, bool discreteCameraXY, bool discreteCameraZ);
	};
}

#endif