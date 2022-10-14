#include "textrenderer.h"
#include <iostream>

namespace LWRL
{
	void TextRenderer::RenderText(glm::vec3 position, glm::vec4 color, std::string text, Font font)
	{
		for (int i = 0; i < text.size(); i++)
		{
			Character character = font.characters[i];

			float xPos = position.x + character.bearing.x;
			float yPos = position.y - (character.size.y - character.bearing.y);

			float width = character.size.x;
			float height = character.size.y;

			spriteRenderer->RenderGlyph({ xPos, yPos, position.z }, color, width, height, character.y, character.u, character.v, font.texture);
		}
	}

	Font* TextRenderer::AddFont(std::string file)
	{
		// Load the font file.
		FT_Face face;

		FT_Error error = FT_New_Face(library, file.c_str(), 0, &face);
		if (error == FT_Err_Unknown_File_Format)
		{
			std::cout << "The font file is openable and readable, but the format is not supported." << std::endl;
			return;
		}
		else if (error)
		{
			std::cout << "The font file is either not openable or not readable." << std::endl;
			return;
		}

		fonts.push_back({ face });
		Font* font = &fonts[fonts.size() - 1];

		// Construct texture.
		unsigned int width = 0;
		unsigned int height = 0;

		unsigned int dataNeeded = 0;

		for (int c = 0; c < face->num_glyphs; c++)
		{
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				std::cout << "Could not load glyph: " + std::to_string(c) + "." << std::endl;
				continue;
			}

			dataNeeded += face->glyph->bitmap.width * face->glyph->bitmap.rows * 4;
			width = std::max(width, face->glyph->bitmap.width);
			height += face->glyph->bitmap.rows;
		}

		unsigned char* data = new unsigned char[dataNeeded];
		unsigned int nextIndex = 0;

		std::vector<Character> characters;

		for (int c = 0; c < face->num_glyphs; c++)
		{
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				std::cout << "Could not load glyph: " + std::to_string(c) + "." << std::endl;
				continue;
			}

			// unsigned int index = (((h + nextY) * width) + w) * 4;
			int w = face->glyph->bitmap.width;
			int h = face->glyph->bitmap.rows;

			unsigned int bitmapLength = w * h * 4;

			for (int i = 0; i < bitmapLength; i += 4)
			{
				data[nextIndex + i + 0] = UCHAR_MAX;
				data[nextIndex + i + 1] = UCHAR_MAX;
				data[nextIndex + i + 2] = UCHAR_MAX;
				data[nextIndex + i + 3] = face->glyph->bitmap.buffer[i / 4];
			}

			Character character =
			{
				glm::vec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::vec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				face->glyph->advance.x,
				nextIndex / height,
				w / width,
				h / height
			};

			font->characters.insert(std::pair<char, Character>(c, character));
			nextIndex += bitmapLength;
		}

		// Now we have all the info we need.
		Texture* texture = new Texture(width, height, data);
		spriteRenderer->AddTexture(texture);
		font->texture = texture;

		return font;
	}

	TextRenderer::TextRenderer(SpriteRenderer* spriteRenderer)
	{
		this->spriteRenderer = spriteRenderer;

		FT_Error error = FT_Init_FreeType(&library);
		if (error)
		{
			std::cout << "An error occurred during FreeType library initialization." << std::endl;
		}
	}
}