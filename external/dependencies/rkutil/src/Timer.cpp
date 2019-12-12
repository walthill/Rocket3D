#include "include/Timer.h"

namespace rkutil
{
	Timer::Timer()
	{
	}

	void Timer::start()
	{
		mStartTime = rk_clock::now();
		mIsPaused = false;
	}

	void Timer::stop()
	{
		mEndTime = rk_clock::now();
	}

	void Timer::pause()
	{
		if (!mIsPaused)
		{
			mEndTime = rk_clock::now();
			mIsPaused = true;
		}
	}

	double Timer::getTimeElapsedMs() const
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

	double Timer::getTimeElapsedInSeconds() const
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
	void Timer::sleepForMilliseconds(double ms)
	{
		std::this_thread::sleep_for(rk_millisecond(ms));
	}

	//Help here https://stackoverflow.com/questions/28311230/precision-time-sleep-using-chrono
	void Timer::sleepUntilElapsed(double msTarget)
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