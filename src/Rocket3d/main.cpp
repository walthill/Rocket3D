/********
	=========================
			 ROCKET3D
	=========================
	File Created By: Walter Hill

	Rocket3D is an open source 3D game engine written using C++ & OpenGL. 

	This code is open source under the Apache 2.0 license.
	(https://github.com/walthill/Rocket3D/blob/master/LICENSE)

	=========================
			 main.cpp
	=========================
	This file is the entry point for the entirety of the Rocket3D game engine.
	The GameApp class is initialized and destroyed here. The engine loop is entered from here.

********/
#include <rkutil/MemoryTracker.h>
#include "../RocketEngine/logging/RK_Log.h"
#include "core/Application.h"

int main(int argc, char* argv[])
{	
	RK_LOGGER_INIT();
	RK_CORE_INFO_ALL("Rocket Logger initialized");

	Application::initInstance();

	if(!Application::getInstance()->run())
		Application::cleanInstance();
	
	//TODO(low): output to logger
	RK_LOGGER_CLEAN();
	rkutil::MemoryTracker::getInstance()->reportAllocs(std::cout);
	system("pause");

	return 0;
}