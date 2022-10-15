#include "textrenderer.h"
#include <iostream>

namespace LWRL
{
	void TextRenderer::RenderText(glm::vec3 position, glm::vec4 color, std::string text, Font* font)
	{
		float x = position.x;

		for (int i = 0; i < text.size(); i++)
		{
			const char c = text[i];
			Character* character = font->characters[c];

			float xPos = x + character->bearing.x;
			float yPos = position.y - (character->size.y - character->bearing.y);

			float width = character->size.x;
			float height = character->size.y;

			spriteRenderer->RenderGlyph({ xPos, yPos, position.z }, color, width, height, character->texture);

			x += (character->advance >> 6);
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
			return nullptr;
		}
		else if (error)
		{
			std::cout << "The font file is either not openable or not readable." << std::endl;
			return nullptr;
		}

		FT_Set_Pixel_Sizes(face, 0, 64);

		Font* font = new Font();
		font->face = face;
		fonts.push_back(font);

		constexpr int ftLoadFlags = FT_LOAD_RENDER | FT_LOAD_COLOR;

		for (unsigned char c = 0; c < 128; c++)
		{
			if (FT_Load_Char(face, c, ftLoadFlags))
			{
				std::cout << "Could not load glyph: " + std::to_string(c) + "." << std::endl;
				continue;
			}

			unsigned int bitmapLength = face->glyph->bitmap.rows * face->glyph->bitmap.width * 4;
			unsigned char* data = new unsigned char[bitmapLength];

			for (int i = 0; i < bitmapLength; i += 4)
			{
				data[i + 0] = UCHAR_MAX;
				data[i + 1] = UCHAR_MAX;
				data[i + 2] = UCHAR_MAX;
				data[i + 3] = face->glyph->bitmap.buffer[i / 4];
			}

			Texture* texture = new Texture(face->glyph->bitmap.width, face->glyph->bitmap.rows, data);

			Character character = {
				glm::vec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::vec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				face->glyph->advance.x,
				texture
			};

			font->characters.insert(std::pair<char, Character*>(c, &character));
		}

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