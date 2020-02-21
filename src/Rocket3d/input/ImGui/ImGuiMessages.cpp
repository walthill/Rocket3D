#include "ImGuiMessages.h"
#include <platform/OpenGL/ImGuiOpenGLRenderer.h>
#include <logging/RK_Log.h>

//TODO: remove GLFW
#include <glfw3.h>

/*
===========================================================

			ImGui Key Up Messages

============================================================
*/

ImGuiKeyUp::ImGuiKeyUp(const int& key)
	:Message(BUTTON_DOWN)
	, mKeyCode(key)
{
}

ImGuiKeyUp::~ImGuiKeyUp()
{
}

void ImGuiKeyUp::process(float deltaTime)
{
	ImGuiIO& io = ImGui::GetIO();
	io.KeysDown[mKeyCode] = false;

	if (mKeyCode == ESC)
	{
	}
	else if (mKeyCode == GLFW_KEY_BACKSPACE)
	{
	}
	else if (mKeyCode == KEY_W)
	{
	}
	else if (mKeyCode == KEY_A)
	{
	}
	else if (mKeyCode == KEY_S)
	{
	}
	else if (mKeyCode == KEY_D)
	{
	}
	else if (mKeyCode == KEY_1)
	{
	}
	else if (mKeyCode == KEY_2)
	{
	}
}


/*
===========================================================

			ImGui Key Down Messages

============================================================
*/

ImGuiKeyDown::ImGuiKeyDown(const int& key, const int& mod)
	:Message(BUTTON_DOWN)
	, mKeyCode(key)
	, mKeyMod(mod)
{
}

ImGuiKeyDown::~ImGuiKeyDown()
{
}

void ImGuiKeyDown::process(float deltaTime)
{
	ImGuiIO& io = ImGui::GetIO();
	io.KeysDown[mKeyCode] = true;

	io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
	io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
	io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
	io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

	if (mKeyCode == ESC)
	{
	}
	else if (mKeyCode == GLFW_KEY_BACKSPACE)
	{
	}
	else if (mKeyCode == KEY_W)
	{
	}
	else if (mKeyCode == KEY_A)
	{
	}
	else if (mKeyCode == KEY_S)
	{
	}
	else if (mKeyCode == KEY_D)
	{
	}
	else if (mKeyCode == KEY_1)
	{
	}
	else if (mKeyCode == KEY_2)
	{
	}
}

/*
===========================================================

			ImGui Key Down Messages

============================================================
*/

ImGuiKeyTyped::ImGuiKeyTyped(const int& key)
	:Message(BUTTON_DOWN)
	, mKeyCode(key)
{
}

ImGuiKeyTyped::~ImGuiKeyTyped()
{
}

void ImGuiKeyTyped::process(float deltaTime)
{
	ImGuiIO& io = ImGui::GetIO();

	if (mKeyCode > 0 && mKeyCode < 0x10000)
	{
		io.AddInputCharacter((unsigned short)mKeyCode);
	}
	else
	{
		RK_FATAL_ALL("KeyCode {0} does not exist", mKeyCode);
	}
}



/*
===========================================================

			ImGUi Mouse DOWN Messages

============================================================
*/


ImGuiMouseDown::ImGuiMouseDown(const int& mouseKey, double x, double y)
	:Message(MOUSE_DOWN)
	, mMouseCode(mouseKey)
	, x(x)
	, y(y) 
{
}

ImGuiMouseDown::~ImGuiMouseDown()
{
}

void ImGuiMouseDown::process(float deltaTime)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MouseDown[mMouseCode] = true;

	if (mMouseCode == LEFT_MOUSE)
	{
		RK_LOG_C("IMGUI LEFT MOUSE DOWN");
	}
	else if (mMouseCode == RIGHT_MOUSE)
	{
		RK_LOG_C("IMGUI RIGHT MOUSE DOWN");
	}
	else if (mMouseCode == MIDDLE_MOUSE)
	{
		RK_LOG_C("IMGUI MIDDLE MOUSE DOWN");
	}
	else if (mMouseCode == MOUSE_SCROLL)
	{
		io.MouseWheel += (float)y;
		io.MouseWheelH += (float)x;
	}
	else
	{
		RK_WARN_C("MESSAGE TYPE NOT REGISTERED FOR MOUSE DOWN MSG");
	}

}


/*
===========================================================

			ImGUi Mouse UP Messages

============================================================
*/


ImGuiMouseUp::ImGuiMouseUp(const int& mouseKey, double x, double y)
	:Message(MOUSE_UP)
	, mMouseCode(mouseKey)
	, x(x)
	, y(y)
{
}

ImGuiMouseUp::~ImGuiMouseUp()
{
}

void ImGuiMouseUp::process(float deltaTime)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MouseDown[mMouseCode] = false;

	if (mMouseCode == LEFT_MOUSE)
	{
		RK_LOG_C("IMGUI LEFT MOUSE UP");
	}
	else if (mMouseCode == RIGHT_MOUSE)
	{
//		io.MouseDown[mMouseCode] = false;
		RK_LOG_C("IMGUI RIGHT MOUSE UP");
	}
	else
	{
		RK_WARN_C("MESSAGE TYPE NOT REGISTERED FOR MOUSE UP MSG");
	}

}



/*
===========================================================

			ImGUi Mouse MOVE Messages

============================================================
*/


ImGuiMouseMove::ImGuiMouseMove(const int& mouseKey, double x, double y)
	:Message(MOUSE_MOVE_TYPE)
	, mMouseMoveCode(mouseKey)
	, xPos(x)
	, yPos(y)
{
}

ImGuiMouseMove::~ImGuiMouseMove()
{
}

void ImGuiMouseMove::process(float deltaTime)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MousePos = ImVec2((float)xPos, (float)yPos);
}

ImGuiUilityMsg::ImGuiUilityMsg(const int& utilCode, double x, double y)
	:Message(IMGUI_UTIL_TYPE)
	, mUtilCode(utilCode)
	, mX(x)
	, mY(y)
{
}

ImGuiUilityMsg::~ImGuiUilityMsg()
{
}

void ImGuiUilityMsg::process(float deltaTime)
{
	if (mUtilCode == WIND_RESIZE)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2((float)mX, (float)mY);
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);	
	}
	else
	{
		RK_WARN_C("MESSAGE TYPE NOT REGISTERED FOR UTILITY MSG");
	}
}