/*
 * Debug.h
 *
 *  Created on: Jun 8, 2013
 *      Author: Bogdan
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#import "Timer.h"

#define DEBUG_MODE 1
#define DEBUG_MODE_NO_COLLISION 0
#define DEBUG_MODE_COLLISION_TEST 0

class Debug
{
public:
	Debug();
	~Debug();
	void DebugScreen();
	void InitBenchmark();
	void StartBenckmark();
	void EndBenchmark();

private:
	void DisplayBenchmark();
	int GetFrameRate();
	int mFrameCounter;
	int mFrameRate;
	Timer* mDebugTimer;
};

#endif /* DEBUG_H_ */
