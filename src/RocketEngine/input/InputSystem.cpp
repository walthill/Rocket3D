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

#include "InputSystem.h"
#include <glfw3.h>

#pragma region GLFW Callbacks

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_move_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_click_callback(GLFWwindow* window, int button, int action, int modifier);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void framebuffer_size_callback(GLFWwindow* window, int width, int height) //TODO: move to callback class
{
	InputSystem* wind = reinterpret_cast<InputSystem*>(glfwGetWindowUserPointer(window));
	wind->onWindowResize(width, height);
}

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


InputSystem::InputSystem(Window* window)
{
	mIsPlayMode = false;
	mpAppInput = new AppInputSender();
//	mpImGuiInput = new ImGuiInputSender();
	mpGameInput = new GameInputSender();

	mpWindow = window;
	GLFWwindow* wind = mpWindow->getWindowHandle();

	//give this class "user" access to callbacks
	glfwSetWindowUserPointer(mpWindow->getWindowHandle(), reinterpret_cast<void*>(this));

	glfwSetCursorPosCallback(wind, mouse_move_callback);
	glfwSetScrollCallback(wind, scroll_callback);
	glfwSetMouseButtonCallback(wind, mouse_click_callback);
	glfwSetKeyCallback(wind, key_callback);
	glfwSetFramebufferSizeCallback(wind, framebuffer_size_callback);
}

void InputSystem::onMouseScroll(double xoffset, double yoffset)
{
	mpGameInput->setPlayMode(mIsPlayMode);
	mpGameInput->onMouseScroll(xoffset, yoffset);

	mpAppInput->onMouseScroll(xoffset, yoffset);
}

void InputSystem::onMouseClick(int button, int action, int modifier)
{
	mpGameInput->setPlayMode(mIsPlayMode);
	mpGameInput->handleMouseButtonEvents(button, action, modifier);

	mpAppInput->handleMouseButtonEvents(button, action, modifier);
}

void InputSystem::onMouseMove(double xpos, double ypos)
{
	if (mIsPlayMode)
	{
		if (modeSwitched)
		{
			modeSwitched = false;
			mpGameInput->setFirstMouse(true);
		}
	}
	else
	{
		if (!modeSwitched)
			modeSwitched = true;
	}

	mpGameInput->setPlayMode(mIsPlayMode);
	mpGameInput->onMouseMove(xpos, ypos);

	mpAppInput->onMouseMove(xpos, ypos);
}


void InputSystem::onKeyEvent(int key, int scancode, int action, int mods)
{
	mpGameInput->setPlayMode(mIsPlayMode);
	mpGameInput->handleKeyEvents(key, scancode, action, mods);
	
	mpAppInput->handleKeyEvents(key, scancode, action, mods);
}

void InputSystem::onWindowResize(int width, int height)
{
	mpWindow->setViewport(0, 0, width, height);
}

void InputSystem::processInput()
{
	//Check and call events
	mpGameInput->setPlayMode(mIsPlayMode);
	mpGameInput->processInput(mpWindow);

	glfwPollEvents();
}
