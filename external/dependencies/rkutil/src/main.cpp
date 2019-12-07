#include <iostream>
#include "include/Timer.h"

void testTimer()
{
	rkutil::Timer tmr;
	tmr.start();
	double t;

	for (size_t i = 0; i < 10000; i++)
	{
		std::cout << "~ TESTING TIMER ~" << std::endl;
	}
	
	tmr.pause(); //stops time tracking

	std::cout << "~|| SLEEPING ||~" << std::endl;

	tmr.sleepForMilliseconds(3000);
	t = tmr.getTimeElapsedMs();
	std::cout << t << "ms" << std::endl;

	t = tmr.getTimeElapsedInSeconds();
	std::cout << t << "sec" << std::endl;
}


int main()
{
	testTimer();
	return 0;
}