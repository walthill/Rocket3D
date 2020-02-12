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

#include "core/GameApp.h"
#include "../RocketEngine/logging/RK_Log.h"
#include "core/Application.h"

int main(int argc, char* argv[])
{	
	RK_LOGGER_INIT();
	RK_CORE_INFO_ALL("Rocket Logger initialized");

	Application *client = new Application();
	client->run();
	delete client;

	//TODO(low): output to logger
	RK_INFO_C("Client leaks: ");
	rkutil::MemoryTracker::getInstance()->reportAllocs(std::cout);

	RK_LOGGER_CLEAN();
	system("pause");

	/*	GameApp::initInstance();

	if (!GameApp::getInstance()->initialize(argv))
	{
		RK_CORE_FATAL_ALL("ERROR: DISPLAY CREATION FAILED.");
		return -1;
	}

	if (!GameApp::getInstance()->processLoop())
	{
		GameApp::getInstance()->cleanInstance();
		
		RK_LOGGER_CLEAN();

		//TODO(low): output to logger
		rkutil::MemoryTracker::getInstance()->reportAllocs(std::cout);
		system("pause");

		return 1;
	}*/

	return 0;
}