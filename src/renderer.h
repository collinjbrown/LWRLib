#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <array>

#include "archtexture.h"
#include "shader.h"
#include "polygons.h"

struct Batch
{
	static constexpr int MAX_TRIS = 20000;

	std::array<Triangle, MAX_TRIS> buffer;
	int index = 0;
};

class Renderer
{
private:
	std::vector<Batch> batches;
	Shader shader;

	glm::mat4		view;
	glm::mat4		projection;

	Archtexture* archtexture;
	std::vector<Texture*> textures;

	GLuint VAO;
	GLuint VBO;

	void RepairTexture();

	void Flush(const Batch& batch);
	void ResetBuffers();

public:
	Texture* GetTexture(int index);

	void RenderSprite(int x, int y, int z, Texture* texture);

	void UpdateProjection(int width, int height, float zoom, float nearClip, float farClip);

	void Render();
	void Terminate();

	Renderer();
};

#endif