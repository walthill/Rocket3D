/********
	=========================
			 ROCKET ENGINE
	=========================
	File Created By: Walter Hill

	Rocket3D is an open source 3D game engine written using C++ & OpenGL.

	This code is open source under the Apache 2.0 license.
	(https://github.com/walthill/Rocket3D/blob/master/LICENSE)

	=========================
			 EngineUtils.h
	=========================
	This file contains common includes and defeinitions to be used in the engine.

********/


#ifndef ENGINE_UTLIS_H
#define ENGINE_UTLIS_H

#define PURE_VIRTUAL =0

#include <string>
#include <vector>
#include <rkutil/Trackable.h>
#include "../logging/RK_Log.h"

typedef unsigned int uint32;
typedef uint32 ComponentId;
typedef uint32 GameObjectId;
typedef std::string ShaderKey;
const double FRAME_TIME_60FPS = 16.7;
const double FRAME_TIME_30FPS = 33.3;

#endif // !ENGINE_UTLIS_H
