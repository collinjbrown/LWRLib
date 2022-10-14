#ifndef RENDERER_H
#define RENDERER

#include <vector>
#include <array>
#include <string>

#include <glm/glm.hpp>

#include "archtexture.h"
#include "shader.h"
#include "polygons.h"

namespace LWRL
{
	struct Batch
	{
		static constexpr int MAX_TRIS = 20000;

		std::array<Triangle, MAX_TRIS> buffer;
		int index = 0;
	};

	class Renderer
	{
	private:
		bool init = false;

		std::vector<Batch> batches;
		Shader shader;

		glm::mat4		view;
		glm::mat4		projection;

		Archtexture* archtexture;
		std::vector<Texture*> textures;

		int tris = 0;

		GLuint VAO;
		GLuint VBO;

		void RepairTexture();

		void Flush(const Batch& batch);
		void ResetBuffers();

	public:
		int GetTris() { return tris; }
		void SetTris(int t) { tris = t; }
		void AddTris(int t) { tris += t; }

		int GetBatchesSize() { return batches.size(); }
		void AddBatch(Batch* b) { batches.push_back(*b); }
		Batch* GetBatch(int ind) { return &batches[ind]; }

		Texture* AddTexture(std::string file);
		Texture* GetTexture(int index);

		void SetView(glm::mat4 view) { this->view = view; }

		void UpdateProjection(int width, int height, float zoom, float nearClip, float farClip);

		void Render();
		void Terminate();

		Renderer(std::string vertexShader, std::string fragmentShader);
	};
}

#endif