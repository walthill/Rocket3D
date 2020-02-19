#include "AppInputSender.h"
#include "../../Rocket3d/core/Application.h"
#include "../../Rocket3d/input/AppMessages.h"
#include <glfw3.h>

AppInputSender::AppInputSender()
{
}

AppInputSender::~AppInputSender()
{
}

bool AppInputSender::handleKeyEvents(int key, int scancode, int action, int mods)
{
	bool shouldConsumeEvent = false;

	onKeyDown(key, scancode, action, mods);
	onKeyUp(key, scancode, action, mods);
	onKeyRepeat(key, scancode, action, mods);

	return shouldConsumeEvent;
}

bool AppInputSender::handleMouseButtonEvents(int key, int action, int mods)
{
	bool shouldConsumeEvent = false;

	return shouldConsumeEvent;
}

void AppInputSender::onKeyDown(int key, int scancode, int action, int mods)
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

void AppInputSender::onKeyUp(int key, int scancode, int action, int mods)
{
}

void AppInputSender::onKeyRepeat(int key, int scancode, int action, int mods)
{
}



void AppInputSender::onMouseDown(int key, int action, int mods)
{
}

void AppInputSender::onMouseUp(int key, int action, int mods)
{
}

void AppInputSender::onMouseMove(double xPos, double yPos)
{
}

void AppInputSender::onMouseScroll(double xoffset, double yoffset)
{
}


