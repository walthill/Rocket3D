#include "GameLayer.h"
#include "../core/GameApp.h"
#include <logging/RK_Log.h>

GameLayer::GameLayer()
	:Layer("Game")
{
	GameApp::initInstance();
	mpGameInstance = GameApp::getInstance();
	
	if (!mpGameInstance->initialize())
	{
		RK_CORE_FATAL_ALL("ERROR: RENDERER CREATION FAILED.");
		return;
	}
}

GameLayer::~GameLayer()
{
	mpGameInstance->cleanInstance();
}

void GameLayer::onUpdate()
{
	mpGameInstance->processLoop();
}