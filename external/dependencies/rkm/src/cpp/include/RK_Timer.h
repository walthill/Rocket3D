#ifndef RK_TIMER_H
#define RK_TIMER_H

//Code used and modified from tzutalin on Github https://gist.github.com/tzutalin/fd0340a93bb8d998abb9

#include <chrono>
#include <thread>

typedef long long int64;
typedef unsigned long long uint64;

class RK_Timer {
	public:
		RK_Timer() {}

		void start() { mStartTime = rk_clock::now(); };
		
		double getTimeElapsedMs() const 
		{
			return std::chrono::duration_cast<rk_millisecond>(
				rk_clock::now() - mStartTime).count();
		}

		double getTimeElapsedInSeconds() const
		{
			return std::chrono::duration_cast<rk_second>(
				rk_clock::now() - mStartTime).count();
		}

		//Help here https://stackoverflow.com/questions/4184468/sleep-for-milliseconds
		void sleepUntilElapsed(double ms) { std::this_thread::sleep_for(rk_millisecond(ms)); }

	private:
		//param1: An arithmetic type, or a class emulating an arithmetic type, to be used as the type for the internal count.
		//param2: A ratio type that represents the period in seconds. http://www.cplusplus.com/reference/chrono/duration/
		typedef std::chrono::duration<double, std::ratio<1> > rk_second;
		typedef std::chrono::duration<double, std::milli > rk_millisecond;

		typedef std::chrono::high_resolution_clock rk_clock;
		
		std::chrono::time_point<rk_clock> mStartTime;
};

#endif // !RK_TIMER_H
