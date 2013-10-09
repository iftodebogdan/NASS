/*
 * Timer.cpp
 *
 *  Created on: Jun 9, 2013
 *      Author: Bogdan
 */

#include "../Includes/Timer.hpp"

Timer::Timer()
{
	timer_start = getTimer();
	ResetStopwatch();
}

clock_t Timer::getTimer()
{
	return clock();
}

unsigned long Timer::getStartTimeMs()
{
	return ((float)(getTimer() - timer_start) / (CLOCKS_PER_SEC / 1000));
}

void Timer::Sleep(int ms)
{
	clock_t start = getTimer();
	while(start + ((float)ms / 1000 * CLOCKS_PER_SEC) > getTimer());
}

void Timer::ResetStartTime()
{
	timer_start = getTimer();
}

void Timer::ResetStopwatch()
{
	stopwatch_start = getTimer();
}

bool Timer::Stopwatch(int ms)
{
	if(getTimer() > stopwatch_start + ((float)ms / 1000 * CLOCKS_PER_SEC))
	{
		stopwatch_start = getTimer();
		return true;
	}
	else
		return false;
}
