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
		if (mKeyCode == W_KEY)
		{
			pGame->moveForward();
		}
		if (mKeyCode == A_KEY)
		{
			pGame->moveLeft();
		}
		if (mKeyCode == S_KEY)
		{
			pGame->moveBack();
		}
		if (mKeyCode == D_KEY)
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
