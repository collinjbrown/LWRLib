#ifndef POLYGONS_H
#define POLYGONS_H

namespace LWRL
{
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

		// Texture width and height
		float w;
		float h;

		// Where along the x coordinate of the archtexture does
		// this texture begin.
		float d;
	};

	struct Triangle
	{
		Vertex topLeft;
		Vertex bottomRight;
		Vertex bottomLeft;
	};

	struct Quad
	{
		Triangle left;
		Triangle right;
	};
}

#endif