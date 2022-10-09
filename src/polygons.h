#ifndef POLYGONS_H
#define POLYGONS_H

struct Vertex
{
	// Location
	float x;
	float y;
	float z;

	// Color
	float r;
	float g;
	float b;
	float a;

	// The s & t coordinates on the texture.
	float s;
	float t;

	// Where along the x coordinate of the archtexture does
	// this texture begin.
	float textureStart;

	float archWidth;
	float archHeight;
};

struct Triangle
{
	Vertex topLeft;
	Vertex bottomRight;
	Vertex bottomLeft;
};

#endif