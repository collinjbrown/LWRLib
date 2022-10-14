#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include <map>

#include "spriterenderer.h"

#include <ft2build.h>
#include FT_FREETYPE_H


namespace LWRL
{
	struct Character
	{
		glm::ivec2	size;
		glm::ivec2	bearing;
		FT_Pos		advance;

		float		y;
		float		u;
		float		v;
	};

	struct Font
	{
		FT_Face						face;
		Texture*					texture;
		std::map<char, Character>	characters;
	};

	class TextRenderer
	{
	private:
		FT_Library				library;
		SpriteRenderer*			spriteRenderer;

		std::vector<Font>		fonts;

	public:
		Font* AddFont(std::string file);
		void RenderText(glm::vec3 position, glm::vec4 color, std::string text, Font* font);
		TextRenderer(SpriteRenderer* spriteRenderer);
	};
}

#endif