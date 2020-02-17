#include "ImGuiMessages.h"
#include <platform/OpenGL/ImGuiOpenGLRenderer.h>
#include <logging/RK_Log.h>

/*
===========================================================

			ImGUi Mouse DOWN Messages

============================================================
*/


ImGuiMouseDown::ImGuiMouseDown(const int& mouseKey, double x, double y)
	:Message(BUTTON_DOWN)
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
		RK_LOG_C("IMGUI RIGHT MOUSE DOWN");
	}
	if (mMouseCode == MIDDLE_MOUSE_DOWN)
	{
		RK_LOG_C("IMGUI MIDDLE MOUSE DOWN");
	}
	if (mMouseCode == MOUSE_SCROLL)
	{
	}
}
	
