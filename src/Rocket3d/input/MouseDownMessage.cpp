#include "MouseDownMessage.h"
#include "../core/GameApp.h"
#include "../../RocketEngine/logging/RK_Log.h"
#include "../../RocketEngine/core/EngineCore.h"
#include "../../RocketEngine/render/Camera.h"

GameMouseDown::GameMouseDown(const int & mouseKey, double x, double y)
	:Message(BUTTON_DOWN)
	,mMouseCode(mouseKey)
	,x(x)
	,y(y)
{
}

GameMouseDown::~GameMouseDown()
{
}

void GameMouseDown::process(float deltaTime)
{
	GameApp* pGame = GameApp::getInstance();

	if (pGame != nullptr)
	{
		if (mMouseCode == LEFT_MOUSE_DOWN)
		{
			RK_LOG_C("LEFT MOUSE DOWN");
		}
		if (mMouseCode == RIGHT_MOUSE_DOWN)
		{
			RK_LOG_C("RIGHT MOUSE DOWN");
		}
		if (mMouseCode == MIDDLE_MOUSE_DOWN)
		{
			RK_LOG_C("MIDDLE MOUSE DOWN");
		}
		if (mMouseCode == MOUSE_SCROLL)
		{
			pGame->getInstance()->getRocketEngine()->getCamera()->processMouseScroll((float)y);

		}
	}
}
