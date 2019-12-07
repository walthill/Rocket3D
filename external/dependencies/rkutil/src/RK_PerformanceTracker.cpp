#include "include/RK_PerformanceTracker.h"

namespace rkutil
{
	RK_PerformanceTracker::RK_PerformanceTracker()
	{
	}

	RK_PerformanceTracker::~RK_PerformanceTracker()
	{
		std::map<std::string, RK_Timer*>::iterator iter;
		for (iter = mTimerMap.begin(); iter != mTimerMap.end(); ++iter)
			delete iter->second;
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
			RK_Timer* pTimer = new RK_Timer();
			pTimer->start();
			mTimerMap[timerName] = pTimer;
		}
	}

	void RK_PerformanceTracker::stopTracking(const std::string& timerName)
	{
		auto iter = mTimerMap.find(timerName);

		if (iter != mTimerMap.end())
			iter->second->pause();
	}

	double RK_PerformanceTracker::getElapsedTime(const std::string& timerName)
	{
		auto iter = mTimerMap.find(timerName);
		if (iter != mTimerMap.end())
			return iter->second->getTimeElapsedMs();
		else
			return 0.0;
	}

	void RK_PerformanceTracker::removeTracker(const std::string& timerName)
	{
		auto iter = mTimerMap.find(timerName);
		if (iter != mTimerMap.end())
		{
			delete iter->second;
			mTimerMap.erase(iter);
		}

	}
}