#include "Editor.h"

Editor* Editor::mpEditor = nullptr;

Editor::~Editor()
{
	clean();
}

bool Editor::initialize(EngineCore* engineHandle)
{
	rkutil::PerformanceTracker* pPerformanceTracker = new rkutil::PerformanceTracker();
	pPerformanceTracker->startTracking(mINIT_TRACKER_NAME);

	mpEngineHandle = engineHandle;

	delete pPerformanceTracker;

	mpAppHandle = Application::getInstance();
	mKeepRunning = true;

	return true;
}

void Editor::clean()
{
}

bool Editor::processLoop()
{

	mpPerformanceTracker = new rkutil::PerformanceTracker();
	mpFrameTimer = new rkutil::Timer();

	
	mpPerformanceTracker->startTracking(mLOOP_TRACKER_NAME);

	mpFrameTimer->start();

	mpPerformanceTracker->startTracking(mDRAW_TRACKER_NAME);

	update();
	render();

	mpPerformanceTracker->stopTracking(mDRAW_TRACKER_NAME);
	//mpFrameTimer->sleepUntilElapsed(FRAME_TIME_60FPS);
	mpPerformanceTracker->stopTracking(mLOOP_TRACKER_NAME);

	//RK_INFO_C("loop took:" + std::to_string(mpPerformanceTracker->getElapsedTime(mLOOP_TRACKER_NAME)) +
	//	"ms draw took:" + std::to_string(mpPerformanceTracker->getElapsedTime(mDRAW_TRACKER_NAME)) + "ms\n");
	//mFPS = (int)(1000.0 / mpPerformanceTracker->getElapsedTime(mDRAW_TRACKER_NAME));
	//RK_INFO_C("FPS: " + std::to_string(mFPS));

	return mKeepRunning;
}

void Editor::update()
{
}

void Editor::render()
{
	//render identally to the game scene BUT w/ different camera & editor gizmos
}