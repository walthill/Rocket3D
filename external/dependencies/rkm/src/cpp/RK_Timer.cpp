#include "include/RK_Timer.h"

RK_Timer::RK_Timer()
{
}

void RK_Timer::start()
{
	mStartTime = rk_clock::now();
}

double RK_Timer::getTimeElapsedMs() const
{
	return std::chrono::duration_cast<rk_millisecond>(
		rk_clock::now() - mStartTime).count();
}

double RK_Timer::getTimeElapsedInSeconds() const
{
	return std::chrono::duration_cast<rk_second>(
		rk_clock::now() - mStartTime).count();
}

//Help here https://stackoverflow.com/questions/4184468/sleep-for-milliseconds
void RK_Timer::sleepUntilElapsed(double ms)
{
	std::this_thread::sleep_for(rk_millisecond(ms)); 
}
