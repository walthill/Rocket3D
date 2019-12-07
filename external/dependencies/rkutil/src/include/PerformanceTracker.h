#ifndef RK_PERFORMANCE_TRACKER_H
#define RK_PERFORMANCE_TRACKER_H

#include <string>
#include <map>
#include "Timer.h"

namespace rkutil
{
	class PerformanceTracker
	{
	public:
		PerformanceTracker();
		~PerformanceTracker();

		void startTracking(const std::string& timerName);
		void stopTracking(const std::string& timerName);
		double getElapsedTime(const std::string& timerName);
		void removeTracker(const std::string& timerName);

	private:
		std::map<std::string, Timer*> mTimerMap;
	};
}
#endif // !RK_PERFORMANCE_TRACKER_H
