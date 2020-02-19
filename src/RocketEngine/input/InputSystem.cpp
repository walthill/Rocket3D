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
#include "../../Rocket3d/input/MessageManager.h"
#include "../../Rocket3d/input/AppMessages.h"
#include "../../Rocket3d/input/ImGui/ImGuiMessages.h"
#include "../../Rocket3d/input/game/GameMessages.h"
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
		mpGameInput->onMouseScroll(xoffset, yoffset);
	}
	else
	{
		mpImGuiInput->onMouseScroll(xoffset, yoffset);
	}

	mpAppInput->onMouseScroll(xoffset, yoffset);
}

void InputSystem::onMouseClick(int button, int action, int modifier)
{
	if (mPlayMode)
	{
		mpGameInput->handleMouseButtonEvents(button, action, modifier);
	}
	else
	{
		mpImGuiInput->handleMouseButtonEvents(button, action, modifier);		
	}

	mpAppInput->handleMouseButtonEvents(button, action, modifier);
}

void InputSystem::onMouseMove(double xpos, double ypos)
{
	if (mPlayMode)
	{
		mpGameInput->onMouseMove(xpos, ypos);
	}
	else
	{
		mpImGuiInput->onMouseMove(xpos, ypos);
	}

	mpAppInput->onMouseMove(xpos, ypos);
}


void InputSystem::onKeyEvent(int key, int scancode, int action, int mods)
{
	if (mPlayMode)
	{
		mpGameInput->handleKeyEvents(key, scancode, action, mods);
	}
	else
	{
		mpImGuiInput->handleKeyEvents(key, scancode, action, mods);
	}

	mpAppInput->handleKeyEvents(key, scancode, action, mods);
}

InputSystem::InputSystem(GLFWwindow* window)
{
	mpAppInput = new AppInputSender();
	mpImGuiInput = new ImGuiInputSender();
	mpGameInput = new GameInputSender();

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

/*
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
}*/

