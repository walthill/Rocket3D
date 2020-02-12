#include "Application.h"

Application::Application()
{
	mIsRunning = true;
	addLayer(new GameLayer());
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
}

void Application::addOverlay(Layer* overlay)
{
	mLayerStack.pushOverlay(overlay);
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