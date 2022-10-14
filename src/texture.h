#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

namespace LWRL
{
	class Texture
	{
	private:
		unsigned int		width;
		unsigned int		height;
		unsigned char*		data;

	public:
		unsigned int		index;
		bool				used;
		bool				active;
		unsigned int		yIndex;

		unsigned int GetWidth() { return width; }
		unsigned int GetHeight() { return height; }
		unsigned char* GetData() { return data; }

		Texture(std::string file, unsigned int index);
		Texture(unsigned int width, unsigned int height, unsigned char* data);
	};
}

#endif