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
	}
}
