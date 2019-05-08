#include "InputSystem.h"
#include <glfw3.h>
#include "../../Rocket3d/core/GameApp.h"
#include "../../Rocket3d/input/KeyDownMessage.h"

InputSystem::InputSystem(GLFWwindow* window)
{
	mpWindowHandle = window;
}

void InputSystem::processInput()
{
	bool escapeKeyPressed = glfwGetKey(mpWindowHandle, GLFW_KEY_ESCAPE) == GLFW_PRESS;

	if (escapeKeyPressed)
	{
		GameMessage* pMessage = new KeyDownMessage(ESC);
		GameApp::getInstance()->addInputMessage(pMessage, 1);
	}
}