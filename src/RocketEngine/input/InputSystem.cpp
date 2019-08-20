#include "InputSystem.h"
#include <glfw3.h>
#include "../../Rocket3d/core/GameApp.h"
#include "../../Rocket3d/input/KeyDownMessage.h"
#include "../../Rocket3d/input/GameMessageManager.h"

InputSystem::InputSystem(GLFWwindow* window)
{
	mpWindowHandle = window;
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
		GameMessage* pMessage = new KeyDownMessage(W_KEY);
		GameApp::getInstance()->getGameMessageManager()->addMessage(pMessage, 1);
	}
	if (glfwGetKey(mpWindowHandle, GLFW_KEY_S) == GLFW_PRESS)
	{
		GameMessage* pMessage = new KeyDownMessage(S_KEY);
		GameApp::getInstance()->getGameMessageManager()->addMessage(pMessage, 1);
	}
	if (glfwGetKey(mpWindowHandle, GLFW_KEY_A) == GLFW_PRESS)
	{
		GameMessage* pMessage = new KeyDownMessage(A_KEY);
		GameApp::getInstance()->getGameMessageManager()->addMessage(pMessage, 1);
	}
	if (glfwGetKey(mpWindowHandle, GLFW_KEY_D) == GLFW_PRESS)
	{
		GameMessage* pMessage = new KeyDownMessage(D_KEY);
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