/*
 * Timer.hpp
 *
 *  Created on: Jun 9, 2013
 *      Author: Bogdan
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <time.h>

class Timer
{
public:
	Timer();
	unsigned long getStartTimeMs();
	void Sleep(int ms);
	void ResetStartTime();
	void ResetStopwatch();
	bool Stopwatch(int ms);

private:
	clock_t getTimer();
	clock_t timer_start;
	clock_t stopwatch_start;
};

#endif /* TIMER_H_ */
