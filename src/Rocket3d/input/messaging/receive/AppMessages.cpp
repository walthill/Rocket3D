#include "AppMessages.h"
#include "../../../core/Application.h"
#include <logging/RK_Log.h>

AppKeyDown::AppKeyDown(const int& key)
	:Message(BUTTON_DOWN)
	, mKeyCode(key)
{
}

AppKeyDown::~AppKeyDown()
{
}

void AppKeyDown::process(float deltaTime)
{
	Application* app = Application::getInstance();

	if (mKeyCode == ESC)
	{
		app->quit();
	}
	else if (mKeyCode == ENTER)
	{
		RK_LOG_C("PLAY MODE TOGGLE");
		app->play();
	}
}
