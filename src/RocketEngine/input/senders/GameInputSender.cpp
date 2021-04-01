#include "GameInputSender.h"
#include "../../../Rocket3d/input/game/GameMessages.h"
#include "../../../Rocket3d/input/game/EditorMessages.h"
#include "../../../Rocket3d/core/Application.h"
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

bool GameInputSender::handleMouseButtonEvents(int key, int action, int mods, double xpos, double ypos)
{
	bool shouldConsumeEvent = false;

	onMouseDown(key, action, mods, xpos, ypos);
	onMouseUp(key, action, mods, xpos, ypos);

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

	if (mInPlayMode)
	{
		Message* pMessage = new GameMouseMove(CAM_MOUSE_MOVE, xOffset, yOffset);
		Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
	}
	else
	{
		if (mEnableEditorMouseMove)
		{
			Message* pMessage = new EditorMouseMove(CAM_MOUSE_MOVE, xOffset, yOffset);
			Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
		}
	}
}

void GameInputSender::onMouseScroll(double xoffset, double yoffset)
{
	Message* pMessage = nullptr;

	if (mInPlayMode)
	{
		pMessage = new GameMouseDown(MOUSE_SCROLL, xoffset, yoffset);
	}
	else
	{
		pMessage = new EditorMouseDown(MOUSE_SCROLL, xoffset, yoffset);
	}
	

	Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
}

void GameInputSender::onKeyDown(int key, int scancode, int action, int mods) //TODO: make editor mouse move require a modifier. Right click? Shift?
{
	if (mInPlayMode)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
		}
		if (key == GLFW_KEY_W && action == GLFW_PRESS)
		{
		}
		if (key == GLFW_KEY_S && action == GLFW_PRESS)
		{
		}
		if (key == GLFW_KEY_A && action == GLFW_PRESS)
		{
		}
		if (key == GLFW_KEY_D && action == GLFW_PRESS)
		{
		}
		if (key == GLFW_KEY_1 && action == GLFW_PRESS)
		{
		}
		if (key == GLFW_KEY_2 && action == GLFW_PRESS)
		{
		}
		if (key == GLFW_KEY_B && action == GLFW_PRESS)
		{
		}
	}
	else
	{
		if (key == GLFW_KEY_Q && action == GLFW_PRESS)
		{
			Message* pMessage = new EditorKeyDown(KEY_Q);
			Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
		}
		if (key == GLFW_KEY_E && action == GLFW_PRESS)
		{
			Message* pMessage = new EditorKeyDown(KEY_E);
			Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
		}
		if (key == GLFW_KEY_I && action == GLFW_PRESS)
		{
		}
		if (key == GLFW_KEY_J && action == GLFW_PRESS)
		{
		}
		if (key == GLFW_KEY_K && action == GLFW_PRESS)
		{
		}
		if (key == GLFW_KEY_L && action == GLFW_PRESS)
		{
		}
		if (key == GLFW_KEY_W && action == GLFW_PRESS)
		{
		}
		if (key == GLFW_KEY_S && action == GLFW_PRESS)
		{
		}
		if (key == GLFW_KEY_A && action == GLFW_PRESS)
		{
		}
		if (key == GLFW_KEY_B && action == GLFW_PRESS)
		{
			Message* pMessage = new EditorKeyDown(KEY_B);
			Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
		}
		if (key == GLFW_KEY_D && action == GLFW_PRESS)
		{
		}
		if (key == GLFW_KEY_1 && action == GLFW_PRESS)
		{
		}
		if (key == GLFW_KEY_2 && action == GLFW_PRESS)
		{
		}
	}
}

void GameInputSender::onKeyUp(int key, int scancode, int action, int mods)
{
	if (mInPlayMode)
	{

	}
	else
	{
	}
}

void GameInputSender::onKeyRepeat(int key, int scancode, int action, int mods)
{
}

//TODO: do mouse selection raycast here
void GameInputSender::onMouseDown(int key, int action, int mods, double xpos, double ypos)
{
	if (mInPlayMode) //GAME
	{
		if (key == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		{
			Message* pMessage = new GameMouseDown(LEFT_MOUSE, xpos, ypos);
			Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
		}
		if (key == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
		{
			Message* pMessage = new GameMouseDown(RIGHT_MOUSE, xpos, ypos);
			Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
		}
		if (key == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
		{
			Message* pMessage = new GameMouseDown(MIDDLE_MOUSE, xpos, ypos);
			Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
		}
	}
	else 		//EDITOR
	{
		if (key == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		{
			Message* pMessage = new EditorMouseDown(LEFT_MOUSE, xpos, ypos);
			Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
		}
		if (key == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
		{
			mEnableEditorMouseMove = true;

			Message* pMessage = new EditorMouseDown(RIGHT_MOUSE, xpos, ypos);
			Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
		}
		if (key == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
		{
			Message* pMessage = new EditorMouseDown(MIDDLE_MOUSE, xpos, ypos);
			Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
		}

	}
}

void GameInputSender::onMouseUp(int key, int action, int mods, double xpos, double ypos)
{
	if (mInPlayMode)
	{
		if (key == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
		{
		}
		if (key == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
		{
		}
		if (key == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE)
		{
		}
	}
	else
	{
		if (key == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
		{
		}
		if (key == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
		{
			mEnableEditorMouseMove = false;
		}
		if (key == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE)
		{
		}
	}
}

void GameInputSender::processInput(Window* wind)
{
	GLFWwindow* windowHandle = wind->getWindowHandle();

	if (mInPlayMode)
	{
		if (glfwGetKey(windowHandle, GLFW_KEY_W) == GLFW_PRESS)
		{
			Message* pMessage = new GameKeyDown(KEY_W);
			Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
		}
		if (glfwGetKey(windowHandle, GLFW_KEY_S) == GLFW_PRESS)
		{
			Message* pMessage = new GameKeyDown(KEY_S);
			Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
		}
		if (glfwGetKey(windowHandle, GLFW_KEY_A) == GLFW_PRESS)
		{
			Message* pMessage = new GameKeyDown(KEY_A);
			Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
		}
		if (glfwGetKey(windowHandle, GLFW_KEY_D) == GLFW_PRESS)
		{
			Message* pMessage = new GameKeyDown(KEY_D);
			Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
		}
	}
	else
	{
		if (glfwGetKey(windowHandle, GLFW_KEY_N) == GLFW_PRESS)
		{
			Message* pMessage = new EditorKeyDown(KEY_N);
			Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
		}
		if (glfwGetKey(windowHandle, GLFW_KEY_M) == GLFW_PRESS)
		{
			Message* pMessage = new EditorKeyDown(KEY_M);
			Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
		}
		if (glfwGetKey(windowHandle, GLFW_KEY_I) == GLFW_PRESS)
		{
			Message* pMessage = new EditorKeyDown(KEY_I);
			Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
		}
		if (glfwGetKey(windowHandle, GLFW_KEY_J) == GLFW_PRESS)
		{
			Message* pMessage = new EditorKeyDown(KEY_J);
			Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
		}
		if (glfwGetKey(windowHandle, GLFW_KEY_K) == GLFW_PRESS)
		{
			Message* pMessage = new EditorKeyDown(KEY_K);
			Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
		}
		if (glfwGetKey(windowHandle, GLFW_KEY_L) == GLFW_PRESS)
		{
			Message* pMessage = new EditorKeyDown(KEY_L);
			Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
		}
		if (glfwGetKey(windowHandle, GLFW_KEY_W) == GLFW_PRESS)
		{
			Message* pMessage = new EditorKeyDown(KEY_W);
			Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
		}
		if (glfwGetKey(windowHandle, GLFW_KEY_S) == GLFW_PRESS)
		{
			Message* pMessage = new EditorKeyDown(KEY_S);
			Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
		}
		if (glfwGetKey(windowHandle, GLFW_KEY_A) == GLFW_PRESS)
		{
			Message* pMessage = new EditorKeyDown(KEY_A);
			Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
		}
		if (glfwGetKey(windowHandle, GLFW_KEY_D) == GLFW_PRESS)
		{
			Message* pMessage = new EditorKeyDown(KEY_D);
			Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
		}
		if (glfwGetKey(windowHandle, GLFW_KEY_1) == GLFW_PRESS)
		{
			Message* pMessage = new EditorKeyDown(KEY_1);
			Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
		}
		if (glfwGetKey(windowHandle, GLFW_KEY_2) == GLFW_PRESS)
		{
			Message* pMessage = new EditorKeyDown(KEY_2);
			Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
		}

	}
}

void GameInputSender::setPlayMode(bool isPlayMode)
{
	mInPlayMode = isPlayMode;
}

void GameInputSender::setFirstMouse(bool firstMouse)
{
	mFirstMouse = firstMouse;
}
