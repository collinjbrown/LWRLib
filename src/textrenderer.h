#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include <map>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "spriterenderer.h"

namespace LWRL
{
	struct Character
	{
		glm::ivec2	size;
		glm::ivec2	bearing;
		FT_Pos		advance;

		float		y;
		float		s;
		float		t;
	};

	struct Font
	{
		FT_Face	face;
		std::map<char, Character> characters;
	};

	class TextRenderer
	{
	private:
		FT_Library				library;
		SpriteRenderer*			spriteRenderer;

		std::vector<Font>		fonts;

	public:
		void AddFont(std::string file);
		void RenderText(std::string text, Font font);
		TextRenderer(SpriteRenderer* spriteRenderer);
	};
}

#endif