#ifndef APP_H
#define APP_H

#include <rkutil/Timer.h>
#include "../../RocketEngine/render/layers/LayerStack.h"
#include "../layers/ImGuiLayer.h"
#include "../../RocketEngine/logging/RK_Log.h"
#include "../../RocketEngine/input/InputSystem.h"
#include "../input/MessageManager.h"

//Event system? for layer-unique inputs

enum AppWindowType { GAME_WINDOW = 0, EDITOR_WINDOW, NUM_WINDOW_TYPES };

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
		bool isPlaying();
		unsigned int getRenderTexture(AppWindowType texId);
		void setRenderTexture(AppWindowType type, unsigned int texId);
		void calculateDeltaTime();
		
		inline void quit() { mIsRunning = false; }
		//tracks time since GLFW init
		inline double getTime() { return mpMasterTimer->getTimeElapsedInSeconds(); };
		inline Window* getAppWindow() { return mpAppWindow; };
		inline MessageManager* getMessageManager() { return mpMessageManager;  }

		float mDeltaTime;
	private:
		static Application* mpApplication;
		Application();
		~Application();

		rkutil::Timer* mpMasterTimer;
		float mLastFrame;

		unsigned int mGameWindowTexture, mEditorWindowTexture;
		Window* mpAppWindow; //TODO: use unique _ptr
		ImGuiLayer* mpImGuiLayer; //TODO: use unique _ptr
		InputSystem* mpInputSystem;
		MessageManager* mpMessageManager;
		LayerStack mLayerStack;
		bool mIsRunning;
};

#endif // !APP_H
