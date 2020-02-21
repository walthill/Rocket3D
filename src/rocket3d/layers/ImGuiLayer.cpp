#include "ImGuiLayer.h"

#include <platform/OpenGL/ImGuiOpenGLRenderer.h>
#include "../core/Application.h"
#include <glfw3.h>

//TODO	-- Get imgui ui objects to recieve input --> refactor input system? 
//		-- Create application event system

ImGuiLayer::ImGuiLayer()
:Layer("ImGui")
{
}

ImGuiLayer::~ImGuiLayer()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiLayer::onAttach()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGuiIO& io = ImGui::GetIO();
	io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
	io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

	// TEMPORARY: should eventually use Hazel key codes
	io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
	io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
	io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
	io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
	io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
	io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
	io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
	io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
	io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
	io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
	io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
	io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
	io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
	io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
	io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
	io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
	io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
	io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
	io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
	io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
	io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

	ImGui_ImplOpenGL3_Init("#version 330");
}

void ImGuiLayer::onDetach()
{
}

void ImGuiLayer::onUpdate()
{
	Application* app = Application::getInstance();
	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize = ImVec2((float)app->getAppWindow()->getWidth(), (float)app->getAppWindow()->getHeight());

	float time = (float)glfwGetTime();
	io.DeltaTime = mTime > 0.0 ? (time - mTime) : (1.0f / 60.0f);
	mTime = time;

	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();

	//render
	static bool show = true;
	ImGui::ShowDemoWindow(&show);
	
	// render your GUI
	ImGui::Begin("Demo window");
	ImGui::Button("Hello!");
	ImGui::End();

	//show on screen
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
