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

}

void ImGuiInputSender::onKeyUp(int key, int scancode, int action, int mods)
{

}

void ImGuiInputSender::onKeyRepeat(int key, int scancode, int action, int mods)
{
}

void ImGuiInputSender::onMouseDown(int key, int action, int mods)
{
	if (key == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		Message* pMessage = new ImGuiMouseDown(LEFT_MOUSE_DOWN);
		Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
	}
	if (key == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		Message* pMessage = new ImGuiMouseDown(RIGHT_MOUSE_DOWN);
		Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
	}
}

void ImGuiInputSender::onMouseUp(int key, int action, int mods)
{
	if (key == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		Message* pMessage = new ImGuiMouseDown(LEFT_MOUSE_UP);
		Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
	}
	if (key == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
	{
		Message* pMessage = new ImGuiMouseDown(RIGHT_MOUSE_UP);
		Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
	}
}

void ImGuiInputSender::onMouseMove(double xpos, double ypos)
{
	if (mFirstMouse)
	{
		mLastX = xpos;
		mLastY = ypos;
		mFirstMouse = false;
	}

	float xOffset = (float)(xpos - mLastX);
	float yOffset = (float)(mLastY- ypos);
	mLastY = ypos;
	mLastX = xpos;

	Message* pMessage = new ImGuiMouseMove(MOUSE_MOVE, xOffset, yOffset);
	Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
}

void ImGuiInputSender::onMouseScroll(double xoffset, double yoffset)
{
	Message* pMessage = new ImGuiMouseDown(MOUSE_SCROLL, xoffset, yoffset);
	Application::getInstance()->getMessageManager()->addMessage(pMessage, 1);
}

