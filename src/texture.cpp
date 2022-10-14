#include "texture.h"

#include "external/stb_image.h"

namespace LWRL
{
	Texture::Texture(std::string file, unsigned int index) : used(false), active(false), yIndex(0)
	{
		this->index = index;

		stbi_set_flip_vertically_on_load(true);

		int imageWidth, imageHeight, nrChannels;
		data = stbi_load(file.c_str(), &imageWidth, &imageHeight, &nrChannels, 0);

		this->width = imageWidth;
		this->height = imageHeight;
	}

	Texture::Texture(unsigned int width, unsigned int height, unsigned char* data) : used(false), active(false), yIndex(0), index(0)
	{
		this->width = width;
		this->height = height;
		this->data = data;
	}
}