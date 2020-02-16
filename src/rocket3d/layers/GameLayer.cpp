#include "GameLayer.h"
#include "../core/GameApp.h"
#include <logging/RK_Log.h>

GameLayer::GameLayer()
	:Layer("Game")
{
	GameApp::initInstance();

	if (!GameApp::getInstance()->initialize())
	{
		RK_CORE_FATAL_ALL("ERROR: RENDERER CREATION FAILED.");
		return;
	}
}
GameLayer::~GameLayer()
{
	GameApp::getInstance()->cleanInstance();

	RK_LOG_C("Game Layer Leaks below");
	//TODO(low): output to logger
	rkutil::MemoryTracker::getInstance()->reportAllocs(std::cout);
}

bool GameLayer::onUpdate()
{
	if (!GameApp::getInstance()->processLoop())
	{
		return false;
	}

	return true;
}
