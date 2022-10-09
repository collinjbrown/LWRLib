#ifndef ARCHTEXTURE_H
#define ARCHTEXTURE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "texture.h"

class Archtexture
{
private:
	GLint			id;
	unsigned int	width;
	unsigned int	height;

public:
	GLint GetID() { return id; }
	
	unsigned int GetWidth() { return width; }
	unsigned int GetHeight() { return height; }

	void AddWidth(unsigned int w) { width = std::max(w, width); }
	void AddHeight(unsigned int h) { height += h; }
	
	void Reset();
};

#endif