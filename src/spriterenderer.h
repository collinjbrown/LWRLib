#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include "renderer.h"

namespace LWRL
{
	class SpriteRenderer : public Renderer
	{
	public:
		void RenderSprite(glm::vec3 pos, glm::vec4 color, Texture* texture);
	};
}

#endif