#include "RK_PerformanceTracker.h"

RK_PerformanceTracker::RK_PerformanceTracker()
{
}

RK_PerformanceTracker::~RK_PerformanceTracker()
{
}

void RK_PerformanceTracker::startTracking(const std::string& timerName)
{
	auto iter = mTimerMap.find(timerName);
	
	if (iter != mTimerMap.end())
	{
		iter->second->start();
	}
	else
	{
		RK_Timer *timer = new RK_Timer();
	}
}
