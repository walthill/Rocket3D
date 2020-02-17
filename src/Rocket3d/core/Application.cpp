#include "Application.h"
#include "../layers/GameLayer.h"
#include "../layers/ImGuiLayer.h"

Application* Application::mpApplication = nullptr;

Application::Application()
{
	mIsRunning = true;

	Window::initGLFW();
	
	mpAppWindow = new Window();
	mpAppWindow->initialize(800, 600, "Rocket3D", DEPTH_TEST | AA_MULTISAMPLE | BLEND | CULL_FACE);
}

Application::~Application()
{
	clean();
}

void Application::clean()
{
	delete mpAppWindow;
	Window::destroyGLFW();
}

void Application::init()
{
	addLayer(new ImGuiLayer());
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

bool Application::run()
{
	while (mIsRunning)
	{
		mpAppWindow->clearToColor(0.4f, 0.6f, 0.6f, 1.0f);
		mpAppWindow->clearWindowBuffers(COLOR_BUFFER | DEPTH_BUFFER);

		for (Layer* layer : mLayerStack)
		{
			if (!layer->onUpdate())
			{
				mIsRunning = false;
				break;
			}
		}

		//swap buffer for all draw layers
		mpAppWindow->swapBuffers();
	}

	return false;
}

Window* Application::getAppWindow()
{
	return mpAppWindow;
}