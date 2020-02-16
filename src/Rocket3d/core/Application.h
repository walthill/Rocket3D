#ifndef APP_H
#define APP_H

#include <render/layers/LayerStack.h>
#include <logging/RK_Log.h>
#include "GameApp.h"

//Event system? for layer-unique inputs

class GameLayer : public Layer 
{
	public:
		GameLayer()
			:Layer("Game")
		{
			GameApp::initInstance();
			
			if (!GameApp::getInstance()->initialize())
			{
				RK_CORE_FATAL_ALL("ERROR: RENDERER CREATION FAILED.");
				return;
			}			
		}

		~GameLayer()
		{
			GameApp::getInstance()->cleanInstance();

			RK_LOG_C("Game Layer Leaks below");
			//TODO(low): output to logger
			rkutil::MemoryTracker::getInstance()->reportAllocs(std::cout);
		}

		bool onUpdate() override
		{
			if (!GameApp::getInstance()->processLoop())
			{
				return false;
			}

			return true;
		}
};

class Application
{
	public:
		Application();
		~Application();

		void init();

		void addLayer(Layer* layer);
		void addOverlay(Layer* overlay);

		void run();

	private:
		LayerStack mLayerStack;
		bool mIsRunning;
};

#endif // !APP_H
