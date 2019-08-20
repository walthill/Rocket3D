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


void KeyDownMessage::process()
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
