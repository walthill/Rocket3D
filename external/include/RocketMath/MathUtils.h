#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Mat4.h"

namespace RK_Math
{
	constexpr auto PI = 3.141592653589793238463f;

	static float radToDeg(float rad) { return rad * (180.0f / PI); };
	static float degToRad(float deg) { return deg * (PI / 180.0f); };
	static float pow2(float num) { return num * num; };
	static int   pow2(int num) { return num * num; };
	static float clamp(float val, float min, float max)
	{
		if (val > max)
			val = max;
		if (val < min)
			val = min;

		return val;
	};
}

#endif // !MATH_UTILS_H
