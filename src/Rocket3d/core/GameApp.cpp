/********
	=========================
			 ROCKET3D
	=========================
	File Created By: Walter Hill

	Rocket3D is an open source 3D game engine written using C++ & OpenGL.

	This code is open source under the Apache 2.0 license.
	(https://github.com/walthill/Rocket3D/blob/master/LICENSE)

	=========================
			 GameApp.cpp
	=========================
********/

#include "GameApp.h"
#include <core/EngineCore.h>
#include <iostream>
#include "../input/GameMessage.h"
#include "../input/GameMessageManager.h"
#include "../../RocketEngine/logging/RK_Log.h"

GameApp* GameApp::mpGameApp = nullptr;

GameApp::~GameApp()
{
	clean();
}

bool GameApp::initialize(char* argv[])
{
	rkutil::RK_PerformanceTracker* pPerformanceTracker = new rkutil::RK_PerformanceTracker();
	pPerformanceTracker->startTracking(mINIT_TRACKER_NAME);

	mpRocketEngine = new EngineCore();
	mpGameMessageManager = new GameMessageManager();
	mpMasterTimer = new rkutil::RK_Timer();

	if (!mpRocketEngine->initialize(argv))
		return false;

	pPerformanceTracker->stopTracking(mINIT_TRACKER_NAME);
	RK_INFO_ALL("Time to init: " + std::to_string(pPerformanceTracker->getElapsedTime(mINIT_TRACKER_NAME)) + "ms\n");
	
	delete pPerformanceTracker;

	mShouldExit = false;

	mpMasterTimer->start();

	return true;
}

void GameApp::clean()
{
	delete mpFrameTimer;
	delete mpMasterTimer;
	delete mpGameMessageManager;
	delete mpRocketEngine;
}

bool GameApp::processLoop()
{
	rkutil::RK_PerformanceTracker* pPerformanceTracker = new rkutil::RK_PerformanceTracker();

	mpFrameTimer = new rkutil::RK_Timer();
	
	while (!mShouldExit)
	{
		//pPerformanceTracker->clearTracker(mLOOP_TRACKER_NAME);
		pPerformanceTracker->startTracking(mLOOP_TRACKER_NAME);

		mpFrameTimer->start();

		//pPerformanceTracker->clearTracker(mDRAW_TRACKER_NAME);
		pPerformanceTracker->startTracking(mDRAW_TRACKER_NAME);
	
		update();
		render();

		pPerformanceTracker->stopTracking(mDRAW_TRACKER_NAME);
		mpFrameTimer->sleepUntilElapsed(m60FPS_FRAME_TIME);
		pPerformanceTracker->stopTracking(mLOOP_TRACKER_NAME);

		RK_INFO_C("loop took:" + std::to_string(pPerformanceTracker->getElapsedTime(mLOOP_TRACKER_NAME)) + 
				  "ms draw took:" +  std::to_string(pPerformanceTracker->getElapsedTime(mDRAW_TRACKER_NAME)) +"ms\n");
//		mFPS = (int)(1000.0 / pPerformanceTracker->getElapsedTime(mDRAW_TRACKER_NAME));
//		RK_INFO_C("FPS: " + std::to_string(mFPS));
	}

	delete pPerformanceTracker;

	return false;
}

void GameApp::update()
{
	mpGameMessageManager->processMessagesForThisFrame();
	mpRocketEngine->update(); 
}

void GameApp::render()
{
	mpRocketEngine->render();
}

double GameApp::getCurrentTime() 
{ 
	return mpMasterTimer->getTimeElapsedMs(); 
};

//TODO: everything below this point should be moved into separate classes and accessed via accessor
// -----------------------------------


void GameApp::moveForward() //TODO: add movement functions to a player class
{
	mpRocketEngine->moveCameraForward();
}

void GameApp::moveBack()
{
	mpRocketEngine->moveCameraBack();
}

void GameApp::moveRight()
{
	mpRocketEngine->moveCameraRight();
}

void GameApp::moveLeft()
{
	mpRocketEngine->moveCameraLeft();
}

void GameApp::toggleView(bool displayWireframeMode)
{
	mpRocketEngine->toggleWireframe(displayWireframeMode);
}