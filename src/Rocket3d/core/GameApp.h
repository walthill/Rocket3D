/********
	=========================
			 ROCKET3D
	=========================
	File Created By: Walter Hill

	Rocket3D is an open source 3D game engine written using C++ & OpenGL.

	This code is open source under the Apache 2.0 license.
	(https://github.com/walthill/Rocket3D/blob/master/LICENSE)

	=========================
			 GameApp.h
	=========================
	This file contains function prototypes and class variables for the GameApp class.

	NOTE: As a general rule, file includes should be done in .cpp files.
		  Instead of includes, use forward declarations in header files.

********/

#ifndef GAME_APP_H
#define GAME_APP_H

#include <rkutil/Trackable.h>
#include <rkutil/MemoryTracker.h>
#include <rkutil/PerformanceTracker.h>
#include <string>
#include <cassert>

class EngineCore;
class GameMessage;
class GameMessageManager;
class Timer;
class GameObject;
class GameObjectManager;
class ComponentManager;

class GameApp : public rkutil::Trackable
{
	public:
		#pragma region Static Class Functions
		/***
			* Initializes the global static instance of the GameApp class
		***/
		static void initInstance()
		{
			mpGameApp = new GameApp;
		}

		/***
			* Destroys the global static instance of the GameApp class
		***/
		static void cleanInstance()
		{
			if (mpGameApp != nullptr)
			{
				delete mpGameApp;
				mpGameApp = nullptr;
			}
		}

		/***
			* Accesses the global static instance of the GameApp class.
		***/
		static GameApp* getInstance()
		{
			assert(mpGameApp != nullptr);
			return mpGameApp;
		}
		#pragma endregion

		/***
			* Instatiate engine, logging, timing, & game variables
			* Returns true on successful initialization, false on failure
		***/
		bool initialize(char * argv[]);
		
		/***
			* Destruction & garbage collection of engine, logging, timing, & game variables
		***/
		void clean();
		
		/***
			* Performs logic updates & rendering every frame. Can run at 30/60fps 
			* Returns true as long as game loop is running. Returns false if user exits game loop.
		***/
		bool processLoop();

		#pragma region Getters and Setters
		/***
			* Accessor for the EngineCore class. Allows for function calls to engine components.
			* Returns a pointer to the EngineCore class.
		***/
		inline EngineCore* getRocketEngine() { return mpRocketEngine; };
		
		/***
			* Accessor for the GameMessageManager class. Allows for function calls to the message system.
			* Returns a pointer to the GameMessageManager class.
		***/
		inline GameMessageManager* getGameMessageManager() { return mpGameMessageManager; };
		
		inline GameObjectManager* getGameObjectManager() { return mpGameObjectManager; }
		inline ComponentManager* getComponentManager() { return mpComponentManager; }

		/***
			* Returns a double representing the runtime of the engine since startup.
		***/
		double getCurrentTime();
		void moveForward();
		void moveBack();
		void moveRight();
		void moveLeft();
		void toggleView(bool displayWireframeMode);
		void quit() { mShouldExit = true; };
		#pragma endregion

	private:
		EngineCore* mpRocketEngine;
		GameMessageManager* mpGameMessageManager;
		GameObjectManager* mpGameObjectManager;
		ComponentManager* mpComponentManager;

		//GameObject* g;
			
		//Game state vars
		static GameApp* mpGameApp;
		bool mShouldExit;

		//Performance tracker data
		rkutil::Timer* mpFrameTimer;
		rkutil::Timer* mpMasterTimer;
		int mFPS;
		const std::string mINIT_TRACKER_NAME = "init";
		const std::string mDRAW_TRACKER_NAME = "draw";
		const std::string mLOOP_TRACKER_NAME = "loop";
		const double m60FPS_FRAME_TIME = 16.7;
		const double m30FPS_FRAME_TIME = 33.3;
		const int MAX_NUM_OBJECTS = 10;
		const float mWindowWidth = 800, mWindowHeight = 600;


		GameApp() {}; //Empty constuctor
		~GameApp();

		void update();
		void render();
};

#endif // !GAME_APP_H
