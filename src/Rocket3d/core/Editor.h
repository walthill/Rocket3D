#ifndef ROCKET_EDITOR_H
#define ROCKET_EDITOR_H

#include <cassert>
#include <rkutil/PerformanceTracker.h>
#include <util/EngineUtils.h>
#include <core/EngineCore.h>
#include "Application.h"

class Editor : public rkutil::Trackable
{
	public:
		#pragma region Static Class Functions
		/***
			* Initializes the global static instance of the GameApp class
		***/
		static void initInstance() 
		{ 
			mpEditor = new Editor; 
		}

		/***
			* Destroys the global static instance of the GameApp class
		***/
		static void cleanInstance()
		{
			if (mpEditor != nullptr)
			{
				delete mpEditor;
				mpEditor = nullptr;
			}
		}

		/***
			* Access the global static instance of the GameApp class.
		***/
		static Editor* getInstance()
		{
			assert(mpEditor != nullptr);
			return mpEditor;
		}
		#pragma endregion

		bool initialize(EngineCore* engineHandle);
		void clean();

		bool processLoop();

	private:
		Application* mpAppHandle;
		EngineCore* mpEngineHandle;

		//State vars
		static Editor* mpEditor;
		bool mKeepRunning = false;

		//Performance tracking
		rkutil::PerformanceTracker* mpPerformanceTracker;
		rkutil::Timer* mpFrameTimer;
		int mFPS = 0;
		const std::string mINIT_TRACKER_NAME = "init";
		const std::string mDRAW_TRACKER_NAME = "draw";
		const std::string mLOOP_TRACKER_NAME = "loop";

		Editor() {};
		~Editor();

		void update();
		void render();
};

#endif // !ROCKET_EDITOR_H
