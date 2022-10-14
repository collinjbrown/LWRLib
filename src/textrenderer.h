#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include "spriterenderer.h"

#include <ft2build.h>
#include FT_FREETYPE_H

namespace LWRL
{
	class TextRenderer : public Renderer
	{
	private:
		FT_Library  library;
		FT_Face     face;

	public:
		void RenderText(glm::vec3 pos, glm::vec4 color, std::string text);

		void Init();
	};
}

#endif