#include "ImGuiMessages.h"
#include <platform/OpenGL/ImGuiOpenGLRenderer.h>
#include <logging/RK_Log.h>

/*
===========================================================

			ImGui Key Down Messages

============================================================
*/

ImGuiKeyDown::ImGuiKeyDown(const int& key)
	:Message(BUTTON_DOWN)
	, mKeyCode(key)
{
}

ImGuiKeyDown::~ImGuiKeyDown()
{
}

void ImGuiKeyDown::process(float deltaTime)
{
	if (mKeyCode == ESC)
	{
	}
	if (mKeyCode == KEY_W)
	{
	}
	if (mKeyCode == KEY_A)
	{
	}
	if (mKeyCode == KEY_S)
	{
	}
	if (mKeyCode == KEY_D)
	{
	}
	if (mKeyCode == KEY_1)
	{
	}
	if (mKeyCode == KEY_2)
	{
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
	if (mMouseCode == LEFT_MOUSE_DOWN)
	{
		io.MouseDown[mMouseCode] = true;
		RK_LOG_C("IMGUI LEFT MOUSE DOWN");
	}
	if (mMouseCode == RIGHT_MOUSE_DOWN)
	{
		io.MouseDown[mMouseCode] = true;
		RK_LOG_C("IMGUI RIGHT MOUSE DOWN");
	}
	if (mMouseCode == MIDDLE_MOUSE_DOWN)
	{
		io.MouseDown[mMouseCode] = true;
		RK_LOG_C("IMGUI MIDDLE MOUSE DOWN");
	}
	if (mMouseCode == MOUSE_SCROLL)
	{
		io.MouseWheel += (float)y;
		io.MouseWheelH += (float)x;
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

	if (mMouseCode == LEFT_MOUSE_UP)
	{
		RK_LOG_C("IMGUI LEFT MOUSE UP");
	}
	if (mMouseCode == RIGHT_MOUSE_UP)
	{
		io.MouseDown[mMouseCode] = false;
		RK_LOG_C("IMGUI RIGHT MOUSE UP");
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
	io.MousePos = ImVec2(xPos, yPos);
}
