#include "MouseMoveMessage.h"
#include "../core/GameApp.h"
#include "../../RocketEngine/logging/RK_Log.h"
#include "../../RocketEngine/core/EngineCore.h"
#include "../../RocketEngine/render/Camera.h"

MouseMoveMessage::MouseMoveMessage(const int & mouseKey, double x, double y)
	:GameMessage(BUTTON_DOWN)
	,mMouseMoveCode(mouseKey)
{
	xPos = (float)x;
	yPos = (float)y;
}

MouseMoveMessage::~MouseMoveMessage()
{
}

void MouseMoveMessage::process()
{
	GameApp* pGame = GameApp::getInstance();

	if (pGame != nullptr)
	{
		if (mMouseMoveCode == CAM_MOUSE_MOVE)
		{
			pGame->getRocketEngine()->getCamera()->processMouseMovement(xPos, yPos);
		}
	}
}
