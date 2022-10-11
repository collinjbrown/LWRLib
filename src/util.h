#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <glm/glm.hpp>

namespace LWRL::UTIL
{
	struct Filter
	{
		std::string name;
		glm::vec4 color;
		float strength;
	};

	glm::vec4 ColorLerp(glm::vec4 a, glm::vec4 b, float t);
}

#endif