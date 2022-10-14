#include "spriterenderer.h"

#include <iostream>
#include <filesystem>
#include <glm/ext/matrix_clip_space.hpp>

namespace LWRL
{
	void SpriteRenderer::UpdateProjection(int width, int height, float zoom, float nearClip, float farClip)
	{
		float halfWidth = (width / 2.0f) * zoom;
		float halfHeight = (height / 2.0f) * zoom;

		this->projection = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, nearClip, farClip);
	}

	Texture* SpriteRenderer::AddTexture(std::string file)
	{
		Texture* texture = new Texture(file, textures.size());
		textures.push_back(texture);
		return texture;
	}

	void SpriteRenderer::AddTexture(Texture* texture)
	{
		texture->index = textures.size();
		textures.push_back(texture);
	}

	Texture* SpriteRenderer::GetTexture(int index)
	{
		if (index < textures.size() && index >= 0)
		{
			return textures[index];
		}

		std::cout << "Texture not found at given index." << std::endl;
		return nullptr;
	}

	void SpriteRenderer::RepairTexture()
	{
		std::vector<Texture*> activeTextures;
		archtexture->Reset();

		for (int i = 0; i < textures.size(); i++)
		{
			Texture* t = textures[i];

			if (t->active)
			{
				t->yIndex = archtexture->GetHeight() + 1;
				archtexture->AddWidth(t->GetWidth());
				archtexture->AddHeight(t->GetHeight());
				activeTextures.push_back(t);
			}
		}

		// Recreate the archtexture.
		// Bind
		glBindTexture(GL_TEXTURE_2D, archtexture->GetID());

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, archtexture->GetWidth(), archtexture->GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

		// Refill the texture with the proper data.
		int h = 0;
		for (int i = 0; i < activeTextures.size(); i++)
		{
			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, h, activeTextures[i]->GetWidth(), activeTextures[i]->GetHeight(), GL_RGBA, GL_UNSIGNED_BYTE, activeTextures[i]->GetData());
			activeTextures[i]->yIndex = h;
			h += activeTextures[i]->GetHeight();
		}

		// Wrap & Filter Modes
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		// Unbind
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void SpriteRenderer::Flush(const Batch& batch)
	{
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, batch.index * sizeof(Triangle), &batch.buffer[0]);
		glDrawElements(GL_TRIANGLES, batch.index * 3, GL_UNSIGNED_INT, nullptr);
	}

	void SpriteRenderer::ResetBuffers()
	{
		bool needsPreparing = false;

		for (Texture* t : textures)
		{
			if (t->active && !t->used)
			{
				t->active = false;
				needsPreparing = true;
			}
			else if (t->used && !t->active)
			{
				t->active = true;
				needsPreparing = true;
			}

			t->used = false;
		}

		if (needsPreparing) RepairTexture();

		for (Batch& batch : batches) batch.index = 0;

		tris = 0;
	}

	void SpriteRenderer::RenderSprite(glm::vec3 pos, glm::vec4 color, Texture* texture)
	{
		texture->used = true;

		int bNum = tris / Batch::MAX_TRIS;
		if (static_cast<unsigned long long>(bNum) + 1 > batches.size())
		{
			batches.push_back(*(new Batch()));
		}

		Batch& batch = batches[bNum];

		const float right = pos.x + (texture->GetWidth() / 2.0f);
		const float left = pos.x - (texture->GetWidth() / 2.0f);
		const float top = pos.y + (texture->GetHeight() / 2.0f);
		const float bottom = pos.y - (texture->GetHeight() / 2.0f);

		const float r = color.r;
		const float g = color.g;
		const float b = color.b;
		const float a = color.a;

		const float s = texture->yIndex;
		const float w = texture->GetWidth();
		const float h = texture->GetHeight();

		Vertex bottomLeft{ left, bottom, pos.z, r, g, b, a, 0.0, 0.0, w, h, s };
		Vertex bottomRight{ right, bottom, pos.z, r, g, b, a, 1.0, 0.0, w, h, s };
		Vertex topLeft{ left, top, pos.z, r, g, b, a, 0.0, 1.0, w, h, s };
		Vertex topRight{ right, top, pos.z, r, g, b, a, 1.0, 1.0, w, h, s };

		batch.buffer[batch.index] = { bottomLeft, bottomRight, topLeft };
		batch.index++;

		batch.buffer[batch.index] = { bottomRight, topRight, topLeft };
		batch.index++;

		tris += 2;
	}

	void SpriteRenderer::RenderGlyph(glm::vec3 pos, glm::vec4 color, float width, float height, float y, Texture* texture)
	{
		texture->used = true;

		int bNum = tris / Batch::MAX_TRIS;
		if (static_cast<unsigned long long>(bNum) + 1 > batches.size())
		{
			batches.push_back(*(new Batch()));
		}

		Batch& batch = batches[bNum];

		const float right = pos.x + (width / 2.0f);
		const float left = pos.x - (width / 2.0f);
		const float top = pos.y + (height / 2.0f);
		const float bottom = pos.y - (height / 2.0f);

		const float r = color.r;
		const float g = color.g;
		const float b = color.b;
		const float a = color.a;

		const float lX = 0.0;
		const float rX = width / texture->GetWidth();
		const float bY = (y / texture->GetHeight());
		const float tY = bY + (height / texture->GetHeight());
		const float s = texture->yIndex;

		Vertex bottomLeft{ left, bottom, pos.z, r, g, b, a, lX, bY, width, height, s };
		Vertex bottomRight{ right, bottom, pos.z, r, g, b, a, rX, bY, width, height, s };
		Vertex topLeft{ left, top, pos.z, r, g, b, a, lX, tY, width, height, s };
		Vertex topRight{ right, top, pos.z, r, g, b, a, rX, tY, width, height, s };

		batch.buffer[batch.index] = { bottomLeft, bottomRight, topLeft };
		batch.index++;

		batch.buffer[batch.index] = { bottomRight, topRight, topLeft };
		batch.index++;

		tris += 2;
	}

	void SpriteRenderer::Render()
	{
		if (!init)
		{
			init = true;
			RepairTexture();
		}

		shader.Use();
		shader.SetMatrix("MVP", projection * view);
		shader.SetVector2("vertArchSize", glm::vec2(archtexture->GetWidth(), archtexture->GetHeight()));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, archtexture->GetID());

		for (int i = 0; i < batches.size(); i++)
		{
			Flush(batches[i]);
		}

		ResetBuffers();
	}

	void SpriteRenderer::Terminate()
	{
		for (int i = 0; i < textures.size(); i++)
		{
			delete textures[i];
		}

		delete archtexture;
		delete this;
	}

	SpriteRenderer::SpriteRenderer() : batches(1), shader("assets/shaders/base.vert", "assets/shaders/base.frag")
	{
		GLuint IBO;

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glGenBuffers(1, &IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

		glBufferData(GL_ARRAY_BUFFER, Batch::MAX_TRIS * sizeof(Triangle), nullptr, GL_DYNAMIC_DRAW);

		// Coordinates
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, x));
		glEnableVertexAttribArray(0);

		// Color
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, r));
		glEnableVertexAttribArray(1);

		// Texture Coordinates
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, s));
		glEnableVertexAttribArray(2);

		// Texture Dimensions
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, w));
		glEnableVertexAttribArray(3);

		// Texture Start
		glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, d));
		glEnableVertexAttribArray(4);

		unsigned int indices[Batch::MAX_TRIS * 3];
		for (int i = 0; i < Batch::MAX_TRIS; i++)
		{
			const int offset = 3 * i;

			indices[offset + 0] = offset + 0;
			indices[offset + 1] = offset + 1;
			indices[offset + 2] = offset + 2;
		}

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glUseProgram(shader.ID);
		GLint location = glGetUniformLocation(shader.ID, "batchTextures");

		int samplers[1];
		samplers[0] = 0;

		glUniform1iv(location, 1, samplers);

		archtexture = new Archtexture();
	}
}