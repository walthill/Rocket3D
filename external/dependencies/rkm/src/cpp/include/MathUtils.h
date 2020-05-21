#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "MatProj.h"

namespace rkm
{
	constexpr auto PI = 3.141592653589793238463f;
	const float epsilon = 0.00001f;

	inline static float radToDeg(float rad) { return rad * (180.0f / PI); };
	inline static float degToRad(float deg) { return deg * (PI / 180.0f); };
	inline static float pow2(float num) { return num * num; };
	inline static int   pow2(int num) { return num * num; };
	inline static float clamp(float val, float min, float max)
	{
		if (val > max) return max;
		if (val < min) return min;
	};
}

#endif // !MATH_UTILS_H
