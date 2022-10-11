#include "util.h"

namespace LWRL::UTIL
{
	glm::vec4 ColorLerp(glm::vec4 a, glm::vec4 b, float t)
	{
		return glm::vec4(	a.r + (b.r - a.r) * t,
							a.g + (b.g - a.g) * t,
							a.b + (b.b - a.b) * t,
							a.a + (b.a - a.a) * t);
	}
}
