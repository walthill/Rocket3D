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
#include "InputSystem.h"
#include "../logging/RK_Log.h"
#include "../../Rocket3d/core/Application.h"
#include "../core/EngineCore.h"
#include "../../Rocket3d/input/messaging/MessageManager.h"
#include "../../Rocket3d/input/messaging/receive/AppMessages.h"
#include "../../Rocket3d/input/messaging/receive/ImGui/ImGuiMessages.h"
#include "../../Rocket3d/input/messaging/receive/game/GameMessages.h"
#include "../../Rocket3d/input/messaging/send/AppInputSender.h"
#include <glfw3.h>

#pragma region GLFW Callbacks
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_move_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_click_callback(GLFWwindow* window, int button, int action, int modifier);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	InputSystem* wind = reinterpret_cast<InputSystem*>(glfwGetWindowUserPointer(window));
	wind->onKeyEvent(key, scancode, action, mods);
}

void mouse_click_callback(GLFWwindow* window, int button, int action, int modifier)
{
	InputSystem* wind = reinterpret_cast<InputSystem*>(glfwGetWindowUserPointer(window));
	wind->onMouseClick(button, action, modifier);
}

//Help found here https://stackoverflow.com/questions/27387040/referencing-glfws-callback-functions-from-a-class
void mouse_move_callback(GLFWwindow* window, double xpos, double ypos)
{
	InputSystem* wind = reinterpret_cast<InputSystem*>(glfwGetWindowUserPointer(window));
	wind->onMouseMove(xpos, ypos);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	InputSystem* wind = reinterpret_cast<InputSystem*>(glfwGetWindowUserPointer(window));
	wind->onMouseScroll(xoffset, yoffset);
}

#pragma endregion


void InputSystem::onMouseScroll(double xoffset, double yoffset)
{
	if (mPlayMode)
	{
		Message* pMessage = new GameMouseDown(MOUSE_SCROLL, xoffset, yoffset);
		Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
	}
}

void InputSystem::onMouseClick(int button, int action, int modifier)
{
	if (mPlayMode)
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		{
			Message* pMessage = new GameMouseDown(LEFT_MOUSE_DOWN);
			Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
		}
		if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
		{
			Message* pMessage = new GameMouseDown(RIGHT_MOUSE_DOWN);
			Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
		}

		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) //TODO: mouse button & key button release
		{
		}
	}
	else
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		{
			Message* pMessage = new ImGuiMouseDown(LEFT_MOUSE_DOWN);
			Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
		}
		if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
		{
			Message* pMessage = new ImGuiMouseDown(RIGHT_MOUSE_DOWN);
			Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
		}
	}
}

void InputSystem::onMouseMove(double xpos, double ypos)
{
	if (mPlayMode)
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

		Message* pMessage = new GameMouseMove(CAM_MOUSE_MOVE, xOffset, yOffset);
		Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
	}
}


void InputSystem::onKeyEvent(int key, int scancode, int action, int mods)
{
	mpAppInput->handleKeyEvents(key, scancode, action, mods);

	//if play mode
		//gameInput->handleKeyEvents()
	//if !play mode
		//editorInput->handleKeyEvents()
}

InputSystem::InputSystem(GLFWwindow* window)
{
	mpAppInput = new AppInputSender();

	firstMouse = true;
	mpWindowHandle = window;
	glfwSetWindowUserPointer(mpWindowHandle, reinterpret_cast<void*>(this));//<--- right here
	glfwSetCursorPosCallback(mpWindowHandle, mouse_move_callback);
	glfwSetScrollCallback(mpWindowHandle, scroll_callback);
	glfwSetMouseButtonCallback(mpWindowHandle, mouse_click_callback);
	glfwSetKeyCallback(window, key_callback);
}

void InputSystem::processInput()
{
	//Check and call events
	glfwPollEvents();
}


void InputSystem::pollGameInput(int key, int scancode, int action, int mods)
{
	if (glfwGetKey(mpWindowHandle, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		Message* pMessage = new GameKeyDown(ESC);
		Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
	}
	if (glfwGetKey(mpWindowHandle, GLFW_KEY_W) == GLFW_PRESS)
	{
		Message* pMessage = new GameKeyDown(KEY_W);
		Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
	}
	if (glfwGetKey(mpWindowHandle, GLFW_KEY_S) == GLFW_PRESS)
	{
		Message* pMessage = new GameKeyDown(KEY_S);
		Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
	}
	if (glfwGetKey(mpWindowHandle, GLFW_KEY_A) == GLFW_PRESS)
	{
		Message* pMessage = new GameKeyDown(KEY_A);
		Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
	}
	if (glfwGetKey(mpWindowHandle, GLFW_KEY_D) == GLFW_PRESS)
	{
		Message* pMessage = new GameKeyDown(KEY_D);
		Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
	}
	if (glfwGetKey(mpWindowHandle, GLFW_KEY_1) == GLFW_PRESS)
	{
		Message* pMessage = new GameKeyDown(KEY_1);
		Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
	}
	if (glfwGetKey(mpWindowHandle, GLFW_KEY_2) == GLFW_PRESS)
	{
		Message* pMessage = new GameKeyDown(KEY_2);
		Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
	}
}

