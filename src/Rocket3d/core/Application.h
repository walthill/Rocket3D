#ifndef APP_H
#define APP_H

#include <rkutil/Trackable.h>
#include <rkutil/PerformanceTracker.h>
#include <rkutil/Timer.h>
#include "../../RocketEngine/window/Window.h"
#include "../../RocketEngine/render/layers/LayerStack.h"
#include "../../RocketEngine/logging/RK_Log.h"
#include "../../RocketEngine/input/InputSystem.h"

//Event system? for layer-unique inputs

class Application : public rkutil::Trackable
{
	public:
		#pragma region Static Class Functions
		/***
			* Initializes the global static instance of the Application
		***/
		static void initInstance()
		{
			mpApplication = new Application;
			mpApplication->init();
		}

		/***
			* Destroys the global static instance of the Application
		***/
		static void cleanInstance()
		{
			if (mpApplication != nullptr)
			{
				delete mpApplication;
				mpApplication = nullptr;
			}
		}

		/***
			* Accesses the global static instance of the Application.
		***/
		static Application* getInstance()
		{
			assert(mpApplication != nullptr);
			return mpApplication;
		}
		#pragma endregion

		void clean();
		void init();

		void addLayer(Layer* layer);
		void addOverlay(Layer* overlay);

		bool run();

		Window* getAppWindow(); 

	private:
		static Application* mpApplication;
		Application();
		~Application();

		Window* mpAppWindow;
		InputSystem* mpInputSystem;
		LayerStack mLayerStack;
		bool mIsRunning;
};

#endif // !APP_H
