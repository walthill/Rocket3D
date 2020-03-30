#include "GameLayer.h"
#include <logging/RK_Log.h>

GameLayer::GameLayer()
	:Layer("Game")
{
	GameApp::initInstance();
	mpGameInstance = GameApp::getInstance();
	
	//NOTE: Game class will own the renderer
	if (!mpGameInstance->initialize())
	{
		RK_CORE_FATAL_ALL("ERROR: GAME CREATION FAILED.");
		return;
	}

	Editor::initInstance();
	mpEditorInstance = Editor::getInstance();

	if (!mpEditorInstance->initialize(mpGameInstance->getRocketEngine()))
	{
		RK_CORE_FATAL_ALL("ERROR: EDITOR CREATION FAILED.");
		return;
	}
}

GameLayer::~GameLayer()
{
	mpGameInstance->cleanInstance();
	mpEditorInstance->cleanInstance();
}

void GameLayer::onUpdate()
{
	mpEditorInstance->processLoop();
	mpGameInstance->processLoop();
}