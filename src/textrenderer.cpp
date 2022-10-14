#include "textrenderer.h"
#include <iostream>

namespace LWRL
{
	void TextRenderer::Init()
	{
		FT_Error error = FT_Init_FreeType(&library);
		if (error)
		{
			std::cout << "An error occurred during FreeType library initialization." << std::endl;
		}

		error = FT_New_Face(library, "assets/fonts/Cantarell/Cantarell-Regular.otf", 0, &face);
		if (error == FT_Err_Unknown_File_Format)
		{
			std::cout << "The font file is openable and readable, but the format is not supported." << std::endl;
		}
		else if (error)
		{
			std::cout << "The font file is either not openable or not readable." << std::endl;
		}

		// More...
	}
}