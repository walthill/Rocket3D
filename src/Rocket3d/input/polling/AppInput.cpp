#include "AppInput.h"
#include "../../../Rocket3d/core/Application.h"
#include "../../../Rocket3d/input/messaging/Message.h"
#include "../../../Rocket3d/input/messaging/AppMessages.h"
#include <glfw3.h>

AppInput::AppInput()
{
}

AppInput::~AppInput()
{
}

bool AppInput::handleKeyEvents(int key, int scancode, int action, int mods)
{
	bool shouldConsumeEvent = false;

	onKeyDown(key, scancode, action, mods);

	return shouldConsumeEvent;
}

bool AppInput::handleMouseButtonEvents(int key, int scancode, int action, int mods)
{
	bool shouldConsumeEvent = false;

	return shouldConsumeEvent;
}

void AppInput::onKeyDown(int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
	{
		Message* pMessage = new AppKeyDown(ENTER);
		Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
	}

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		Message* pMessage = new AppKeyDown(ESC);
		Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
	}
}

void AppInput::onKeyUp(int key, int scancode, int action, int mods)
{
}

void AppInput::onKeyRepeat(int key, int scancode, int action, int mods)
{
}

void AppInput::onMouseDown(int key, int scancode, int action, int mods)
{
}

void AppInput::onMouseUp(int key, int scancode, int action, int mods)
{
}

void AppInput::onMouseRepeat(int key, int scancode, int action, int mods)
{
}

