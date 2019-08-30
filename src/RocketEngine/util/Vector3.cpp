/********
	=========================
			 ROCKET MATH
	=========================
	File Created By: Walter Hill

	Rocket3D is an open source 3D game engine written using C++ & OpenGL.

	This code is open source under the Apache 2.0 license.
	(https://github.com/walthill/Rocket3D/blob/master/LICENSE)

	=========================
			 Vector3.cpp
	=========================
	Instatiate static variables
********/

#include <RocketMath/Vector3.h>

Vector3 Vector3::zero(0.0f, 0.0f, 0.0f);
Vector3 Vector3::one(1.0f, 1.0f, 1.0f);
Vector3 Vector3::left(-1.0f, 0.0f, 0.0f);
Vector3 Vector3::right(1.0f, 0.0f, 0.0f);
Vector3 Vector3::up(0.0f, 1.0f, 0.0f);
Vector3 Vector3::down(0.0f, -1.0f, 0.0f);
Vector3 Vector3::forward(0.0f, 0.0f, 1.0f);
Vector3 Vector3::back(0.0f, 0.0f, -1.0f);
