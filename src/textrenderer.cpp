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
			Character character = font->characters[c];

			float xPos = x + character.bearing.x;
			float yPos = position.y - (character.size.y - character.bearing.y);

			float width = character.size.x;
			float height = character.size.y;

			spriteRenderer->RenderGlyph({ xPos, yPos, position.z }, color, width, height, character.y, font->texture);

			x += (character.advance >> 6);
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

		// Construct texture.
		unsigned int width = 0;
		unsigned int height = 0;

		constexpr int ftLoadFlags = FT_LOAD_RENDER | FT_LOAD_COLOR;

		for (unsigned char c = 0; c < 128; c++)
		{
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				std::cout << "Could not load glyph: " + std::to_string(c) + "." << std::endl;
				continue;
			}

			width = std::max(width, face->glyph->bitmap.width);
			height += face->glyph->bitmap.rows;
		}

		if (width == 0 || height == 0)
		{
			std::cout << "Failed to load glyphs." << std::endl;
			return nullptr;
		}

		unsigned char* data = new unsigned char[width * height * 4];

		for (int i = 0; i < width * height * 4; i++) data[i] = '0';

		unsigned int nextIndex = 0;
		unsigned int yIndex = 0;

		std::vector<Character> characters;

		for (unsigned char c = 0; c < 128; c++)
		{
			if (FT_Load_Char(face, c, ftLoadFlags))
			{
				std::cout << "Could not load glyph: " + std::to_string(c) + "." << std::endl;
				continue;
			}
			
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
				yIndex
			};

			font->characters.insert(std::pair<char, Character>(c, character));
			nextIndex += width * h * 4;
			yIndex += h;
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