#include "ImGuiLayer.h"
#include <platform/OpenGL/ImGuiOpenGLRenderer.h>
#include <platform/OpenGL/ImGuiGLFWRenderer.h>
#include "../core/Application.h"
#include <glfw3.h>
//#include <platform\OpenGL\ImGuiGLFWRenderer.cpp>

ImGuiLayer::ImGuiLayer()
:Layer("ImGui")
{
}

ImGuiLayer::~ImGuiLayer()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiLayer::onAttach()
{
	Application* app = Application::getInstance();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
	
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	ImGui_ImplGlfw_InitForOpenGL(app->getAppWindow()->getWindowHandle(), true);
	ImGui_ImplOpenGL3_Init("#version 410"); //TODO: get version from window
}

void ImGuiLayer::onDetach()
{
}

void ImGuiLayer::onUpdate()
{
}

void ImGuiLayer::onImGuiRender()
{
	//render ImGui test window
//	static bool show = true;
//	ImGui::ShowDemoWindow(&show);

	drawDockSpace();
	drawToolbar();
	drawInspector();
	drawSceneTree();
	drawGameWindow();
}

void ImGuiLayer::begin()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void ImGuiLayer::end()
{
	ImGuiIO& io = ImGui::GetIO();

	// Rendering
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}
}

void ImGuiLayer::drawDockSpace()
{
	// DockSpace
	static bool open = true;
	static bool opt_fullscreen_persistant = true;
	bool opt_fullscreen = opt_fullscreen_persistant;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
	// because it would be confusing to have two docking targets within each others.
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	if (opt_fullscreen)
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}

	// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background 
	// and handle the pass-thru hole, so we ask Begin() to not render a background.
	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;

	// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
	// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
	// all active windows docked into it will lose their parent and become undocked.
	// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
	// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("RocketDockSpaceContainer", &open, window_flags);
	ImGui::PopStyleVar();

	if (opt_fullscreen)
		ImGui::PopStyleVar(2);

	// DockSpace
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("RocketDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}

	ImGui::End();
}

void ImGuiLayer::drawToolbar()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New"))
			{

			}
			if (ImGui::MenuItem("Quit"))
			{
				Application::getInstance()->quit();
			}

			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("About"))
			{

			}
			if (ImGui::MenuItem("Documentation"))
			{
			}

			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}
}

void ImGuiLayer::drawInspector()
{
	ImGui::SetNextWindowSize(ImVec2(430, 450), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin("Inspector"))
	{
		ImGui::End();
		return;
	}

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 20));
	ImGui::Separator();
	ImGui::Columns(1);
	ImGui::PopStyleVar();
	ImGui::End();
}

void ImGuiLayer::drawSceneTree()
{
	ImGui::SetNextWindowSize(ImVec2(430, 250), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin("Scene Tree"))
	{
		ImGui::End();
		return;
	}

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 20));
	ImGui::Separator();
	ImGui::Columns(1);
	ImGui::PopStyleVar();
	ImGui::End();
}

void ImGuiLayer::drawGameWindow()
{
	//-- Render game scene to ImGui window - https://gamedev.stackexchange.com/questions/140693/how-can-i-render-an-opengl-scene-into-an-imgui-window

	Application* app = Application::getInstance();
	mGameWindowTexture = (void*)app->getRenderTexture();
	
	//TODO: generalize game render texture width and height

	// My Game has a different viewport than the editor's one:
	const int W = 600;
	const int H = 450;

	// We set the same viewport size (plus margin) to the next window (if first use)
	ImGui::SetNextWindowSize(ImVec2(W+15, H+35), ImGuiCond_Once);

	ImGui::Begin("Game rendering");
	{
		// Get the current cursor position (where your window is)
		ImVec2 pos = ImGui::GetCursorScreenPos();

		app->getAppWindow()->setViewport(0, 0, W, H);

		// Ask ImGui to draw it as an image:
		// Under OpenGL the ImGUI image type is GLuint
		// So make sure to use "(void *)tex" but not "&tex"
		ImGui::GetWindowDrawList()->AddImage(mGameWindowTexture, 
			ImVec2(ImGui::GetItemRectMin().x + 5, ImGui::GetItemRectMin().y+30),
			ImVec2(pos.x + W, pos.y + H), 
			ImVec2(0, 1), ImVec2(1, 0));
	}
	ImGui::End();
}