#include "GameInputSender.h"
#include "../../Rocket3d/input/game/GameMessages.h"
#include "../../Rocket3d/core/Application.h"
#include <glfw3.h>


GameInputSender::GameInputSender() 
	: InputSender()
{
}

GameInputSender::~GameInputSender()
{
}

bool GameInputSender::handleKeyEvents(int key, int scancode, int action, int mods)
{
	bool shouldConsumeEvent = false;

	onKeyDown(key, scancode, action, mods);
	onKeyUp(key, scancode, action, mods);
	onKeyRepeat(key, scancode, action, mods);

	return shouldConsumeEvent;

}

bool GameInputSender::handleMouseButtonEvents(int key, int action, int mods)
{
	bool shouldConsumeEvent = false;

	onMouseDown(key, action, mods);
	onMouseUp(key, action, mods);

	return shouldConsumeEvent;
}

void GameInputSender::onMouseMove(double xPos, double yPos)
{
	if (mFirstMouse)
	{
		mLastX = xPos;
		mLastY = yPos;
		mFirstMouse = false;
	}

	float xOffset = (float)(xPos - mLastX);
	float yOffset = (float)(mLastY - yPos);
	mLastX = xPos;
	mLastY = yPos;

	Message* pMessage = new GameMouseMove(CAM_MOUSE_MOVE, xOffset, yOffset);
	Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
}

void GameInputSender::onMouseScroll(double xoffset, double yoffset)
{
	Message* pMessage = new GameMouseDown(MOUSE_SCROLL, xoffset, yoffset);
	Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
}

void GameInputSender::onKeyDown(int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		Message* pMessage = new GameKeyDown(ESC);
		Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
	}
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		Message* pMessage = new GameKeyDown(KEY_W);
		Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		Message* pMessage = new GameKeyDown(KEY_S);
		Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
	}
	if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		Message* pMessage = new GameKeyDown(KEY_A);
		Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
	}
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		Message* pMessage = new GameKeyDown(KEY_D);
		Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
	}
	if (key == GLFW_KEY_1 && action == GLFW_PRESS)
	{
		Message* pMessage = new GameKeyDown(KEY_1);
		Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
	}
	if (key == GLFW_KEY_2 && action == GLFW_PRESS)
	{
		Message* pMessage = new GameKeyDown(KEY_2);
		Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
	}
}

void GameInputSender::onKeyUp(int key, int scancode, int action, int mods)
{
}

void GameInputSender::onKeyRepeat(int key, int scancode, int action, int mods)
{
}

void GameInputSender::onMouseDown(int key, int action, int mods)
{
	if (key == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		Message* pMessage = new GameMouseDown(LEFT_MOUSE);
		Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
	}
	if (key == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		Message* pMessage = new GameMouseDown(RIGHT_MOUSE);
		Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
	}
}

void GameInputSender::onMouseUp(int key, int action, int mods)
{
	if (key == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
	}
}
