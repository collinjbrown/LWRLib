#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include <vector>
#include <array>

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

	class SpriteRenderer
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
		Texture* AddTexture(std::string file);
		void AddTexture(Texture* texture);
		Texture* GetTexture(int index);

		void SetView(glm::mat4 view) { this->view = view; }

		Quad GenerateQuad(glm::vec3 pos, glm::vec4 color, Texture* texture);

		void RenderSprite(glm::vec3 pos, glm::vec4 color, Texture* texture);
		void RenderQuad(Quad quad, Texture* texture);
		void RenderGlyph(glm::vec3 pos, glm::vec4 color, float width, float height, Texture* texture);

		void UpdateProjection(int width, int height, float zoom, float nearClip, float farClip);

		void Render();
		void Terminate();

		SpriteRenderer();
	};
}

#endif