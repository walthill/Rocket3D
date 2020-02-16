#include "ImGuiLayer.h"

#include <platform/OpenGL/ImGuiOpenGLRenderer.h>
#include <glfw3.h>

//TODO	-- separate glfw init from renderer init
//		-- make application a singleton & have its own window

ImGuiLayer::ImGuiLayer()
:Layer("ImGui")
{
}

ImGuiLayer::~ImGuiLayer()
{
}

void ImGuiLayer::onAttach()
{
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGuiIO& io = ImGui::GetIO();
	io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
	io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

	ImGui_ImplOpenGL3_Init("#version 410");
}

void ImGuiLayer::onDetach()
{
}

bool ImGuiLayer::onUpdate()
{
	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize = ImVec2(800, 600);

	float time = (float)glfwGetTime();
	io.DeltaTime = mTime > 0.0 ? (time - mTime) : (1.0f / 60.0f);
	mTime = time;

	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();

	static bool show = true;
	ImGui::ShowDemoWindow(&show);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	return true;
}
