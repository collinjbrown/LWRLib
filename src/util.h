#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <corecrt_math_defines.h>
#include <iostream>
#include <glm/gtx/norm.hpp>
#include <algorithm>

namespace LWRL::UTIL
{
	struct Quaternion
	{
		float w;
		float x;
		float y;
		float z;

		Quaternion operator*(const Quaternion& rhs) const noexcept
		{
			Quaternion q = { 0, 0, 0, 0 };
			q.w = (this->w * rhs.w - this->x * rhs.x - this->y * rhs.y - this->z * rhs.z);
			q.x = (this->w * rhs.x + this->x * rhs.w + this->y * rhs.z - this->z * rhs.y);
			q.y = (this->w * rhs.y - this->x * rhs.z + this->y * rhs.w + this->z * rhs.x);
			q.z = (this->w * rhs.z + this->x * rhs.y - this->y * rhs.x + this->z * rhs.w);
			return q;
		}

		bool operator==(const Quaternion& rhs) const noexcept
		{
			return ((this->w == rhs.w) && (this->x == rhs.x) && (this->y == rhs.y) && (this->z == rhs.z));
		}

		Quaternion operator-() const noexcept
		{
			return Quaternion{ -this->w, -this->x, -this->y, -this->z };
		}
	};

	struct Filter
	{
		std::string name;
		glm::vec4 color;
		float strength;
	};

	static glm::vec4 ColorLerp(glm::vec4 a, glm::vec4 b, float t);

	static Quaternion Slerp(Quaternion q, Quaternion r, float step);
	static float QuaternionDistance(Quaternion l, Quaternion r);

	static void NormalizeQuaternion(Quaternion& q);
	static Quaternion EulerToQuaternion(glm::vec3 e);
	static glm::vec3 QuaternionToEuler(Quaternion q);

	static glm::vec3 RotateRelative(glm::vec3 relative, glm::vec3 position, Quaternion q);
	static glm::vec3 Rotate(glm::vec3 position, Quaternion q);

	static glm::vec3 Lerp(glm::vec3 a, glm::vec3 b, float step);
}

#endif