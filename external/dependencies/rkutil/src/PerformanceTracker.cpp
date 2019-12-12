#include "include/PerformanceTracker.h"

namespace rkutil
{
	PerformanceTracker::PerformanceTracker()
	{
	}

	PerformanceTracker::~PerformanceTracker()
	{
		std::map<std::string, Timer*>::iterator iter;
		for (iter = mTimerMap.begin(); iter != mTimerMap.end(); ++iter)
			delete iter->second;
	}

	void PerformanceTracker::startTracking(const std::string& timerName)
	{
		auto iter = mTimerMap.find(timerName);

		if (iter != mTimerMap.end())
		{
			iter->second->start();
		}
		else
		{
			Timer* pTimer = new Timer();
			pTimer->start();
			mTimerMap[timerName] = pTimer;
		}
	}

	void PerformanceTracker::stopTracking(const std::string& timerName)
	{
		auto iter = mTimerMap.find(timerName);

		if (iter != mTimerMap.end())
			iter->second->pause();
	}

	double PerformanceTracker::getElapsedTime(const std::string& timerName)
	{
		auto iter = mTimerMap.find(timerName);
		if (iter != mTimerMap.end())
			return iter->second->getTimeElapsedMs();
		else
			return 0.0;
	}

	void PerformanceTracker::removeTracker(const std::string& timerName)
	{
		auto iter = mTimerMap.find(timerName);
		if (iter != mTimerMap.end())
		{
			delete iter->second;
			mTimerMap.erase(iter);
		}

	}
}