/********
	=========================
			 ROCKET MATH
	=========================
	File Created By: Walter Hill

	Rocket3D is an open source 3D game engine written using C++ & OpenGL.

	This code is open source under the Apache 2.0 license.
	(https://github.com/walthill/Rocket3D/blob/master/LICENSE)

	=========================
			 Vector2.cpp
	=========================
	Instatiate static variables
********/

#include <RocketMath/Vector2.h>

Vector2 Vector2::zero(0.0f, 0.0f);
Vector2 Vector2::one(1.0f, 1.0f);
Vector2 Vector2::left(-1.0f, 0.0f);
Vector2 Vector2::right(1.0f, 0.0f);
Vector2 Vector2::up(0.0f, 1.0f);
Vector2 Vector2::down(0.0f, -1.0f);
