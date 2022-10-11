#ifndef UTIL_H
#define UTIL_H

#include <glm/glm.hpp>

namespace LWRL::UTIL
{
	glm::vec4 ColorLerp(glm::vec4 a, glm::vec4 b, float t);
}

#endif