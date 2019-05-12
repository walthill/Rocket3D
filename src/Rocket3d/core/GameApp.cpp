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

	mRocketEngine = new EngineCore();
	mpGameMessageManager = new GameMessageManager();
	
	if (!mRocketEngine->initialize(argv))
		return false;

	mpMasterTimer = new Timer();

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
	delete mRocketEngine;
}

bool GameApp::processLoop()
{
	PerformanceTracker* pPerformanceTracker = new PerformanceTracker();

	mpFrameTimer = new Timer();
	
	while (!mShouldExit)//!glfwWindowShouldClose(window))
	{
		pPerformanceTracker->clearTracker(mLOOP_TRACKER_NAME);
		pPerformanceTracker->startTracking(mLOOP_TRACKER_NAME);

		mpFrameTimer->start();

		pPerformanceTracker->clearTracker(mDRAW_TRACKER_NAME);
		pPerformanceTracker->startTracking(mDRAW_TRACKER_NAME);
	

		update();
		render();


		pPerformanceTracker->stopTracking(mDRAW_TRACKER_NAME);
		mpFrameTimer->sleepUntilElapsed(m30_FRAME_TIME);
		pPerformanceTracker->stopTracking(mLOOP_TRACKER_NAME);

		//		mFPS = (1000.0 / pPerformanceTracker->getElapsedTime(mDRAW_TRACKER_NAME));
//		cout << "loop took:" << pPerformanceTracker->getElapsedTime(mLOOP_TRACKER_NAME) << "ms";
//		cout << " draw took:" << pPerformanceTracker->getElapsedTime(mDRAW_TRACKER_NAME) << "ms\n";

	}

	return false;
}

void GameApp::update()
{
	mRocketEngine->update();
	mpGameMessageManager->processMessagesForThisFrame();

}

void GameApp::render()
{
	mRocketEngine->render();
}

void GameApp::addInputMessage(GameMessage* msg, int delay)
{ 
	mpGameMessageManager->addMessage(msg, delay); 
};

double GameApp::getCurrentTime() 
{ 
	return mpMasterTimer->getElapsedTime(); 
};
