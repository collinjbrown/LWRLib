#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include <map>

#include "polyrenderer.h"

#include <ft2build.h>
#include FT_FREETYPE_H

namespace LWRL
{
	enum class ScreenAnchor { bottomLeft, topLeft, bottomRight, topRight, center };

	struct Character
	{
		glm::ivec2	size;
		glm::ivec2	bearing;
		FT_Pos		advance;

		Texture*	texture;

		Character(glm::ivec2 size, glm::ivec2 bearing, FT_Pos advance, Texture* texture)
		{
			this->size = size;
			this->bearing = bearing;
			this->advance = advance;
			this->texture = texture;
		}
	};

	struct Font
	{
		FT_Face						face;
		std::map<char, Character*>	characters;
	};

	class TextRenderer
	{
	private:
		FT_Library				library;
		PolyRenderer*			spriteRenderer;

		std::vector<Font*>		fonts;
		int						fontSize = 128;

	public:
		Font* AddFont(std::string file);
		void RenderText(glm::vec3 position, glm::vec4 color, std::string text, Font* font, float scale);
		void RenderText(glm::vec3 position, glm::vec4 color, std::string text, Font* font, float scale, float zoom);
		TextRenderer(PolyRenderer* spriteRenderer);
	};
}

#endif