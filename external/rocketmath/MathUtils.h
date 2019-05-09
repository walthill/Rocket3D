#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Mat4.h"

constexpr auto PI = 3.141592653589793238463f;

float RadToDeg(float rad) { return rad * (180.0f / PI); };
float DegToRad(float deg) { return deg * (PI / 180.0f); };

#endif // !MATH_UTILS_H
