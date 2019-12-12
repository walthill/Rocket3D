/********
	=========================
			 ROCKET3D
	=========================
	File Created By: Walter Hill

	This file is based on a similar file
	from Champlain College's EGP-410 (Game AI) course

	Rocket3D is an open source 3D game engine written using C++ & OpenGL.

	This code is open source under the Apache 2.0 license.
	(https://github.com/walthill/Rocket3D/blob/master/LICENSE)

	=========================
			 KeyDownMessage.cpp
	=========================

********/

#include "KeyDownMessage.h"
#include "../core/GameApp.h"

KeyDownMessage::KeyDownMessage(const int& key)
	:GameMessage(BUTTON_DOWN)
	, mKeyCode(key)
{
}

KeyDownMessage::~KeyDownMessage()
{
}

void KeyDownMessage::process(float deltaTime)
{
	GameApp* pGame = GameApp::getInstance();

	if (pGame != nullptr)
	{
		if (mKeyCode == ESC)
		{
			pGame->quit();
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
