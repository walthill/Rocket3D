#include "GameLayer.h"
#include <logging/RK_Log.h>

GameLayer::GameLayer()
	:Layer("Game")
{
	Editor::initInstance();
	mpEditorInstance = Editor::getInstance();

	//TODO: create static init for RocketEngine?

	if (!mpEditorInstance->initialize())
	{
		RK_CORE_FATAL_ALL("ERROR: EDITOR CREATION FAILED.");
		return;
	}

	GameApp::initInstance();
	mpGameInstance = GameApp::getInstance();
	
	if (!mpGameInstance->initialize())
	{
		RK_CORE_FATAL_ALL("ERROR: GAME CREATION FAILED.");
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