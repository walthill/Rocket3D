#include "GameApp.h"
#include <core/EngineCore.h>
#include <iostream>
#include <DeanLib/PerformanceTracker.h>
#include "../input/GameMessage.h"
#include "../input/GameMessageManager.h"

GameApp* GameApp::mpGameApp = nullptr;

GameApp::~GameApp()
{
	clean();
}


bool GameApp::initialize(char* argv[])
{
	PerformanceTracker* pPerformanceTracker = new PerformanceTracker;
	pPerformanceTracker->startTracking(mINIT_TRACKER_NAME);

	mpRocketEngine = new EngineCore();
	mpGameMessageManager = new GameMessageManager();
	mpMasterTimer = new Timer();

	if (!mpRocketEngine->initialize(argv))
		return false;

	pPerformanceTracker->stopTracking(mINIT_TRACKER_NAME);
	std::cout << std::endl << "Time to Init: " << pPerformanceTracker->getElapsedTime(mINIT_TRACKER_NAME) << " ms" << std::endl;

	delete pPerformanceTracker;

	mShouldExit = false;

	mpMasterTimer->start();

	return true;
}

void GameApp::clean()
{
	delete mpGameMessageManager;
	delete mpRocketEngine;
}

bool GameApp::processLoop()
{
	PerformanceTracker* pPerformanceTracker = new PerformanceTracker();

	mpFrameTimer = new Timer();
	
	while (!mShouldExit)
	{
		pPerformanceTracker->clearTracker(mLOOP_TRACKER_NAME);
		pPerformanceTracker->startTracking(mLOOP_TRACKER_NAME);

		mpFrameTimer->start();

		pPerformanceTracker->clearTracker(mDRAW_TRACKER_NAME);
		pPerformanceTracker->startTracking(mDRAW_TRACKER_NAME);
	

		update();
		render();

		pPerformanceTracker->stopTracking(mDRAW_TRACKER_NAME);
		mpFrameTimer->sleepUntilElapsed(m60FPS_FRAME_TIME);
		pPerformanceTracker->stopTracking(mLOOP_TRACKER_NAME);

//		std::cout << "loop took:" << pPerformanceTracker->getElapsedTime(mLOOP_TRACKER_NAME) << "ms";
//		std::cout << " draw took:" << pPerformanceTracker->getElapsedTime(mDRAW_TRACKER_NAME) << "ms\n";
		//mFPS = (int)(1000.0 / pPerformanceTracker->getElapsedTime(mDRAW_TRACKER_NAME));
		//std::cout << "FPS: " << mFPS << "\n";
	}

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

void GameApp::addInputMessage(GameMessage* msg, int delay)
{ 
	mpGameMessageManager->addMessage(msg, delay); 
};

double GameApp::getCurrentTime() 
{ 
	return mpMasterTimer->getElapsedTime(); 
};

void GameApp::moveForward()
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

