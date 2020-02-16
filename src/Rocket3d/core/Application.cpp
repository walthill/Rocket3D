#include "Application.h"
#include "../layers/GameLayer.h"
#include "../layers/ImGuiLayer.h"

Application::Application()
{
	mIsRunning = true;
	addLayer(new GameLayer());	//game layer created by default for now
//	addLayer(new ImGuiLayer());
}

Application::~Application()
{
}

void Application::init()
{
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

void Application::run()
{
	while (mIsRunning)
	{
		for (Layer* layer : mLayerStack)
			if (!layer->onUpdate())
			{
				mIsRunning = false;
				break;
			}
	}
}