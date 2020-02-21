#include "ImGuiInputSender.h"
#include "../../Rocket3d/input/ImGui/ImGuiMessages.h"
#include "../../Rocket3d/core/Application.h"
#include <glfw3.h>

ImGuiInputSender::ImGuiInputSender()
{
}

ImGuiInputSender::~ImGuiInputSender()
{
}

bool ImGuiInputSender::handleKeyEvents(int key, int scancode, int action, int mods)
{
	bool shouldConsumeEvent = false;

	onKeyDown(key, scancode, action, mods);
	onKeyUp(key, scancode, action, mods);
	onKeyRepeat(key, scancode, action, mods);

	return shouldConsumeEvent;
}

bool ImGuiInputSender::handleMouseButtonEvents(int button, int action, int mods)
{
	bool shouldConsumeEvent = false;

	onMouseDown(button, action, mods);
	onMouseUp(button, action, mods);

	return shouldConsumeEvent;
}

void ImGuiInputSender::onKeyDown(int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_BACKSPACE && action == GLFW_PRESS)
	{
		Message* pMessage = new ImGuiKeyDown(GLFW_KEY_BACKSPACE, mods);
		Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
	}
	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
	{
		Message* pMessage = new ImGuiKeyDown(GLFW_KEY_ENTER, mods);
		Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
	}
}

void ImGuiInputSender::onKeyUp(int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_BACKSPACE && action == GLFW_RELEASE)
	{
		Message* pMessage = new ImGuiKeyUp(GLFW_KEY_BACKSPACE);
		Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
	}
	if (key == GLFW_KEY_ENTER && action == GLFW_RELEASE)
	{
		Message* pMessage = new ImGuiKeyUp(GLFW_KEY_ENTER);
		Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
	}
}

void ImGuiInputSender::onKeyRepeat(int key, int scancode, int action, int mods)
{
}

void ImGuiInputSender::onMouseDown(int key, int action, int mods)
{
	if (key == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		Message* pMessage = new ImGuiMouseDown(LEFT_MOUSE);
		Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
	}
	if (key == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		Message* pMessage = new ImGuiMouseDown(RIGHT_MOUSE);
		Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
	}
}

void ImGuiInputSender::onMouseUp(int key, int action, int mods)
{
	if (key == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		Message* pMessage = new ImGuiMouseUp(LEFT_MOUSE);
		Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
	}
	if (key == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
	{
		Message* pMessage = new ImGuiMouseUp(RIGHT_MOUSE);
		Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
	}
}

void ImGuiInputSender::onMouseMove(double xpos, double ypos)
{
	Message* pMessage = new ImGuiMouseMove(MOUSE_MOVE, xpos, ypos);
	Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
}

void ImGuiInputSender::onMouseScroll(double xoffset, double yoffset)
{
	Message* pMessage = new ImGuiMouseDown(MOUSE_SCROLL, xoffset, yoffset);
	Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
}

void ImGuiInputSender::onKeyTyped(int key)
{
	Message* pMessage = new ImGuiKeyTyped(key);
	Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
}

void ImGuiInputSender::onWindowResize(int width, int height)
{
	Message* pMessage = new ImGuiUilityMsg(WIND_RESIZE, width, height);
	Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
}

