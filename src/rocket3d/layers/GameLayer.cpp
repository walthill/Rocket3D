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
}

bool GameLayer::onUpdate()
{
	if (!GameApp::getInstance()->processLoop())
	{
		return false;
	}

	return true;
}
