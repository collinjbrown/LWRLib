#include "spriterenderer.h"

namespace LWRL
{
	void SpriteRenderer::RenderSprite(glm::vec3 pos, glm::vec4 color, Texture* texture)
	{
		texture->used = true;

		int bNum = GetTris() / Batch::MAX_TRIS;
		if (static_cast<unsigned long long>(bNum) + 1 > GetBatchesSize())
		{
			AddBatch(new Batch());
		}

		Batch& batch = *GetBatch(bNum);

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

		AddTris(2);
	}
}