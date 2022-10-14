#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include <ft2build.h>
#include FT_FREETYPE_H

namespace
{
	class TextRenderer
	{
	private:
		FT_Library  library;
		FT_Face     face;

	public:
		void Init();
	};
}

#endif