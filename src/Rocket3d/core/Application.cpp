#include "Application.h"
#include "../layers/GameLayer.h"
#include "../layers/ImGuiLayer.h"

/*	TODO	
 * ============================================================
 *		-- Render game scene to ImGui window - https://gamedev.stackexchange.com/questions/140693/how-can-i-render-an-opengl-scene-into-an-imgui-window
 *		
 *		
 *		
 *		-- Abstract input codes
 *		-- Input polling 
 *		-- fully implement input messaging (flesh out files, etc)
 */


Application* Application::mpApplication = nullptr;

Application::Application()
{
	mIsRunning = true;

	Window::initGLFW();
	mpMasterTimer = new rkutil::Timer();
	mpMasterTimer->start();
	
	mpAppWindow = new Window();
	mpAppWindow->initialize(800, 600, "Rocket3D", DEPTH_TEST | AA_MULTISAMPLE | BLEND | CULL_FACE);
}

Application::~Application()
{
	clean();
}

void Application::clean()
{
	delete mpMessageManager;
	delete mpInputSystem;
	delete mpAppWindow;
	Window::destroyGLFW();
}

void Application::init()
{
	mpMessageManager = new MessageManager();
	mpInputSystem = new InputSystem(mpAppWindow);
	mpImGuiLayer = new ImGuiLayer();

	addOverlay(mpImGuiLayer);
//	addLayer(new ImGuiLayer());
	addLayer(new GameLayer());	//game layer created by default for now
}

void Application::addLayer(Layer* layer)
{
	mLayerStack.pushLayer(layer);
	layer->onAttach();
}

void Application::addOverlay(Layer* overlay)
{
	mLayerStack.pushOverlay(overlay);
	overlay->onAttach();
}

void Application::onMessage(float deltaTime)
{
	mpMessageManager->processMessagesForThisFrame(deltaTime);
}

bool Application::run()
{
	while (mIsRunning)
	{
		mpAppWindow->clearToColor(0.4f, 0.6f, 0.6f, 1.0f);
		mpAppWindow->clearWindowBuffers(COLOR_BUFFER | DEPTH_BUFFER);

		onMessage(mDeltaTime);
		mpInputSystem->processInput();
		calculateDeltaTime();

		for (Layer* layer : mLayerStack)
		{
			layer->onUpdate();
		}

		mpImGuiLayer->begin();
		for (Layer* layer : mLayerStack)
		{
			layer->onImGuiRender();
		}
		mpImGuiLayer->end();

		//swap buffer for all draw layers
		mpAppWindow->swapBuffers();
	}

	return false;
}

void Application::play()
{
	mpInputSystem->play();
}

void Application::calculateDeltaTime()
{
	float currentFrame = (float)getTime();
	mDeltaTime = currentFrame - mLastFrame;
	mLastFrame = currentFrame;
}