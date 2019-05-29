#ifndef GAME_APP_H
#define GAME_APP_H

#include <DeanLib/Trackable.h>
#include <string>
#include <cassert>

// As a general rule, file includes should be done in .cpp files  
// Instead of includes, use forward declarations in header files
class EngineCore;
class GameMessage;
class GameMessageManager;
class Timer;

class GameApp : Trackable
{
	public:
		#pragma region Static Class Functions
		static void initInstance()
		{
			mpGameApp = new GameApp;
		}

		static void cleanInstance()
		{
			if (mpGameApp != nullptr)
			{
				delete mpGameApp;
				mpGameApp = nullptr;
			}
		}

		static GameApp* getInstance()
		{
			assert(mpGameApp != nullptr);
			return mpGameApp;
		}
		#pragma endregion

		bool initialize(char * argv[]);
		void clean();
		bool processLoop();

		#pragma region Getters and Setters
		void addInputMessage(GameMessage* msg, int delay);
		double getCurrentTime();
		void moveForward();
		void moveBack();
		void moveRight();
		void moveLeft();
		void quit() { mShouldExit = true; };
		#pragma endregion

	private:
		EngineCore* mpRocketEngine;
		GameMessageManager* mpGameMessageManager;

		//Game state vars
		static GameApp* mpGameApp;
		bool mShouldExit;

		//Performance tracker data
		Timer *mpFrameTimer;
		Timer *mpMasterTimer;
		int mFPS;
		const std::string mINIT_TRACKER_NAME = "init";
		const std::string mDRAW_TRACKER_NAME = "draw";
		const std::string mLOOP_TRACKER_NAME = "loop";
		const double m60FPS_FRAME_TIME = 16.7;
		const double m30FPS_FRAME_TIME = 33.3;

		GameApp() {}; //Empty constuctor
		~GameApp();

		void update();
		void render();
};

#endif // !GAME_APP_H
