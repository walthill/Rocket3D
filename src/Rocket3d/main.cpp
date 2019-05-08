#include "core/GameApp.h"
#include <iostream>

int main(int argc, char* argv[])
{
	GameApp::initInstance();

	if (!GameApp::getInstance()->initialize(argv))
	{
		std::cout << "ERROR: DISPLAY CREATION FAILED." << std::endl;
		return -1;
	}

	if (!GameApp::getInstance()->processLoop())
	{
		GameApp::getInstance()->cleanInstance();
		return 1;
	}

	return 0;
}