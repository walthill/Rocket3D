#ifndef APP_H
#define APP_H

#include <rkutil/Trackable.h>
#include <rkutil/PerformanceTracker.h>
#include <rkutil/Timer.h>
#include "../../RocketEngine/window/Window.h"
#include "../../RocketEngine/render/layers/LayerStack.h"
#include "../../RocketEngine/logging/RK_Log.h"
#include "../../RocketEngine/input/InputSystem.h"
#include "../input/MessageManager.h"

//Event system? for layer-unique inputs

class Application : public rkutil::Trackable
{
	//TODO: create play button to differentiate between (with bool flag?) inputs to game and to ImGui

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

		void onMessage(float deltaTime);

		bool run();
		void play();
		void calculateDeltaTime();
		
		inline void quit() { mIsRunning = false; }
		//tracks time since GLFW init
		inline double getTime() { return mpMasterTimer->getTimeElapsedMs(); };
		inline Window* getAppWindow() { return mpAppWindow; };
		inline MessageManager* getMessageManager() { return mpMessageManager;  }

		float mDeltaTime;
	private:
		static Application* mpApplication;
		Application();
		~Application();

		rkutil::Timer* mpMasterTimer;
		float mLastFrame;

		Window* mpAppWindow;
		InputSystem* mpInputSystem;
		MessageManager* mpMessageManager;
		LayerStack mLayerStack;
		bool mIsRunning;
};

#endif // !APP_H
