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
#include "../../Rocket3d/core/Application.h"
#include "../core/EngineCore.h"
#include "../../Rocket3d/input/MessageManager.h"
#include "../../Rocket3d/input/ImGui/ImGuiMessages.h"
#include "../../Rocket3d/input/game/GameMessages.h"

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
	Message* pMessage = new GameMouseDown(MOUSE_SCROLL, xoffset, yoffset);
	Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
}

void InputSystem::rk_mouse_click_callback(int button, int action, int modifier)
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

	Message* pMessage = new GameMouseMove(CAM_MOUSE_MOVE, xOffset, yOffset);
	Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
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

	//Check and call events
	glfwPollEvents();
}
