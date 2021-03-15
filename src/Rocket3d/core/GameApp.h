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

#include "../../RocketEngine/util/EngineUtils.h"
#include <rkutil/UtilDefines.h>

class Application;
class EngineCore;
class Message;
class MessageManager;
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
			RK_ASSERT(mpGameApp != nullptr);
			return mpGameApp;
		}
		#pragma endregion

		/***
			* Instatiate engine, logging, timing, & game variables
			* Returns true on successful initialization, false on failure
		***/
		bool initialize();
		
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
			* Returns a double representing the runtime of the engine since startup.
		***/
		double getCurrentTime();
		void moveForward();
		void moveBack();
		void moveRight();
		void moveLeft();
		void toggleView(bool displayWireframeMode);
		#pragma endregion

	private:
		Application* mpAppHandle;
		EngineCore* mpRocketEngine;

		//GameObject* g;
			
		//Game state vars
		static GameApp* mpGameApp;
		bool mKeepRunning = false;

		//Performance tracker data
		rkutil::PerformanceTracker* mpPerformanceTracker;
		rkutil::Timer* mpFrameTimer;
		rkutil::Timer* mpMasterTimer;
		int mFPS = 0;
		const std::string mINIT_TRACKER_NAME = "init";
		const std::string mDRAW_TRACKER_NAME = "draw";
		const std::string mLOOP_TRACKER_NAME = "loop";
		const int MAX_NUM_OBJECTS = 10;

		GameApp() {}; //Empty constuctor
		~GameApp();

		void update();
		void render();
};

#endif // !GAME_APP_H
