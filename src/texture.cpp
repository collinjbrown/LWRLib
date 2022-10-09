#include "texture.h"

#include "external/stb_image.h"

Texture::Texture(std::string file) : used(false), active(false), index(-1)
{
	stbi_set_flip_vertically_on_load(true);

	int imageWidth, imageHeight, nrChannels;
	data = stbi_load(file.c_str(), &imageWidth, &imageHeight, &nrChannels, 0);

	this->width = imageWidth;
	this->height = imageHeight;

	stbi_image_free(data);
}