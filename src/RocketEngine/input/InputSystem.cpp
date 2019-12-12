/********
	=========================
			 ROCKET ENGINE
	=========================
	File Created By: Walter Hill

	Rocket3D is an open source 3D game engine written using C++ & OpenGL.

	This code is open source under the Apache 2.0 license.
	(https://github.com/walthill/Rocket3D/blob/master/LICENSE)

	=========================
			 InputSystem.cpp
	=========================

********/

#include <glad/glad.h>
#include <glfw3.h>
#include "InputSystem.h"
#include "../logging/RK_Log.h"
#include "../../Rocket3d/core/GameApp.h"
#include "../core/EngineCore.h"
#include "../../Rocket3d/input/KeyDownMessage.h"
#include "../../Rocket3d/input/MouseDownMessage.h"
#include "../../Rocket3d/input/GameMessageManager.h"
#include "../../Rocket3d/input/MouseMoveMessage.h"

#pragma region GLFW Callbacks
void mouse_move_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_click_callback(GLFWwindow* window, int button, int action, int modifier);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void mouse_click_callback(GLFWwindow* window, int button, int action, int modifier)
{
	InputSystem* wind = reinterpret_cast<InputSystem*>(glfwGetWindowUserPointer(window));
	wind->rk_mouse_click_callback(button, action, modifier);
}

//Help found here https://stackoverflow.com/questions/27387040/referencing-glfws-callback-functions-from-a-class
void mouse_move_callback(GLFWwindow* window, double xpos, double ypos)
{
	InputSystem* wind = reinterpret_cast<InputSystem*>(glfwGetWindowUserPointer(window));
	wind->rk_mouse_move_callback(xpos, ypos);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	InputSystem* wind = reinterpret_cast<InputSystem*>(glfwGetWindowUserPointer(window));
	wind->rk_scroll_callback(xoffset, yoffset);
}

#pragma endregion


void InputSystem::rk_scroll_callback(double xoffset, double yoffset)
{
	GameMessage* pMessage = new MouseDownMessage(MOUSE_SCROLL, xoffset, yoffset);
	GameApp::getInstance()->getGameMessageManager()->addMessage(pMessage, 1);
}

void InputSystem::rk_mouse_click_callback(int button, int action, int modifier)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		GameMessage* pMessage = new MouseDownMessage(LEFT_MOUSE_DOWN);
		GameApp::getInstance()->getGameMessageManager()->addMessage(pMessage, 1);
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		GameMessage* pMessage = new MouseDownMessage(RIGHT_MOUSE_DOWN);
		GameApp::getInstance()->getGameMessageManager()->addMessage(pMessage, 1);
	}

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
	}
}

void InputSystem::rk_mouse_move_callback(double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xOffset = (float)(xpos - lastX);
	float yOffset = (float)(lastY - ypos);
	lastY = ypos;
	lastX = xpos;

	GameMessage* pMessage = new MouseMoveMessage(CAM_MOUSE_MOVE, xOffset, yOffset);
	GameApp::getInstance()->getGameMessageManager()->addMessage(pMessage, 1);
}

InputSystem::InputSystem(GLFWwindow* window)
{
	firstMouse = true;
	mpWindowHandle = window;
	glfwSetWindowUserPointer(mpWindowHandle, reinterpret_cast<void*>(this));//<--- right here
	glfwSetCursorPosCallback(mpWindowHandle, mouse_move_callback);
	glfwSetScrollCallback(mpWindowHandle, scroll_callback);
	glfwSetMouseButtonCallback(mpWindowHandle, mouse_click_callback);
}

void InputSystem::processInput()
{
	if (glfwGetKey(mpWindowHandle, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		GameMessage* pMessage = new KeyDownMessage(ESC);
		GameApp::getInstance()->getGameMessageManager()->addMessage(pMessage, 1);
	}
	if (glfwGetKey(mpWindowHandle, GLFW_KEY_W) == GLFW_PRESS)
	{
		GameMessage* pMessage = new KeyDownMessage(KEY_W);
		GameApp::getInstance()->getGameMessageManager()->addMessage(pMessage, 1);
	}
	if (glfwGetKey(mpWindowHandle, GLFW_KEY_S) == GLFW_PRESS)
	{
		GameMessage* pMessage = new KeyDownMessage(KEY_S);
		GameApp::getInstance()->getGameMessageManager()->addMessage(pMessage, 1);
	}
	if (glfwGetKey(mpWindowHandle, GLFW_KEY_A) == GLFW_PRESS)
	{
		GameMessage* pMessage = new KeyDownMessage(KEY_A);
		GameApp::getInstance()->getGameMessageManager()->addMessage(pMessage, 1);
	}
	if (glfwGetKey(mpWindowHandle, GLFW_KEY_D) == GLFW_PRESS)
	{
		GameMessage* pMessage = new KeyDownMessage(KEY_D);
		GameApp::getInstance()->getGameMessageManager()->addMessage(pMessage, 1);
	}
	if (glfwGetKey(mpWindowHandle, GLFW_KEY_1) == GLFW_PRESS)
	{
		GameMessage* pMessage = new KeyDownMessage(KEY_1);
		GameApp::getInstance()->getGameMessageManager()->addMessage(pMessage, 1);
	}
	if (glfwGetKey(mpWindowHandle, GLFW_KEY_2) == GLFW_PRESS)
	{
		GameMessage* pMessage = new KeyDownMessage(KEY_2);
		GameApp::getInstance()->getGameMessageManager()->addMessage(pMessage, 1);
	}

	//Check and call events
	glfwPollEvents();
}
