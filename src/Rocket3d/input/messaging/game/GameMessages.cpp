#include "GameMessages.h"
#include "../../../core/GameApp.h"
#include "../../../../RocketEngine/logging/RK_Log.h"
#include "../../../../RocketEngine/core/EngineCore.h"
#include "../../../../RocketEngine/render/Camera.h"

/*
===========================================================

			Game Key Messages

============================================================
*/

GameKeyDown::GameKeyDown(const int& key)
	:Message(BUTTON_DOWN)
	, mKeyCode(key)
{
}

GameKeyDown::~GameKeyDown()
{
}

void GameKeyDown::process(float deltaTime)
{
	GameApp* pGame = GameApp::getInstance();

	if (pGame != nullptr)
	{
		if (mKeyCode == ESC)
		{
//			pGame->quit();
		}
		if (mKeyCode == KEY_W)
		{
			pGame->moveForward();
		}
		if (mKeyCode == KEY_A)
		{
			pGame->moveLeft();
		}
		if (mKeyCode == KEY_S)
		{
			pGame->moveBack();
		}
		if (mKeyCode == KEY_D)
		{
			pGame->moveRight();
		}
		if (mKeyCode == KEY_1)
		{
			pGame->toggleView(false);
		}
		if (mKeyCode == KEY_2)
		{
			pGame->toggleView(true);
		}
	}
}

/*
===========================================================

			Game Mouse DOWN Messages

============================================================
*/


GameMouseDown::GameMouseDown(const int& mouseKey, double x, double y)
	:Message(BUTTON_DOWN)
	, mMouseCode(mouseKey)
	, x(x)
	, y(y)
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

/*
===========================================================

			Game Mouse MOVE Messages

============================================================
*/

GameMouseMove::GameMouseMove(const int& mouseKey, double x, double y)
	:Message(BUTTON_DOWN)
	, mMouseMoveCode(mouseKey)
{
	xPos = (float)x;
	yPos = (float)y;
}

GameMouseMove::~GameMouseMove()
{
}

void GameMouseMove::process(float deltaTime)
{
	GameApp* pGame = GameApp::getInstance();

	if (pGame != nullptr)
	{
		if (mMouseMoveCode == CAM_MOUSE_MOVE)
		{
			pGame->getRocketEngine()->getCamera()->processMouseMovement(deltaTime, xPos, yPos);
		}
	}
}
