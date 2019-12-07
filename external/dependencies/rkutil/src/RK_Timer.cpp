#include "include/RK_Timer.h"

namespace rkutil
{
	RK_Timer::RK_Timer()
	{
	}

	void RK_Timer::start()
	{
		mStartTime = rk_clock::now();
		mIsPaused = false;
	}

	void RK_Timer::stop()
	{
		mEndTime = rk_clock::now();
	}

	void RK_Timer::pause()
	{
		if (!mIsPaused)
		{
			mEndTime = rk_clock::now();
			mIsPaused = true;
		}
	}

	double RK_Timer::getTimeElapsedMs() const
	{
		double elapsedTime = 0;

		if (mIsPaused)
		{
			elapsedTime = std::chrono::duration_cast<rk_millisecond>(
				mEndTime - mStartTime).count();
		}
		else
		{
			elapsedTime = std::chrono::duration_cast<rk_millisecond>(
				rk_clock::now() - mStartTime).count();
		}

		return elapsedTime;
	}

	double RK_Timer::getTimeElapsedInSeconds() const
	{
		double elapsedTime = 0;

		if (mIsPaused)
		{
			elapsedTime = std::chrono::duration_cast<rk_second>(
				mEndTime - mStartTime).count();
		}
		else
		{
			elapsedTime = std::chrono::duration_cast<rk_second>(
				rk_clock::now() - mStartTime).count();
		}

		return elapsedTime;
	}

	//Help here https://stackoverflow.com/questions/4184468/sleep-for-milliseconds
	void RK_Timer::sleepForMilliseconds(double ms)
	{
		std::this_thread::sleep_for(rk_millisecond(ms));
	}

	//Help here https://stackoverflow.com/questions/28311230/precision-time-sleep-using-chrono
	void RK_Timer::sleepUntilElapsed(double msTarget)
	{
		bool shouldSleep = true;
		while (shouldSleep)
		{
			auto now = rk_clock::now();

			auto elapsedTime = std::chrono::duration_cast<rk_millisecond>(now - mStartTime);
			if (elapsedTime.count() > msTarget)
				shouldSleep = false;
		}
	}
}