/*
 * Debug.hpp
 *
 *  Created on: Jun 8, 2013
 *      Author: Bogdan
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#import "Timer.hpp"

/*
#define DEBUG_MODE 0
#define DEBUG_MODE_NO_COLLISION 0
#define DEBUG_MODE_COLLISION_TEST 0
*/

class Debug
{
public:
	Debug();
	~Debug();
	void DebugScreen();
	void InitBenchmark();
	void StartBenckmark();
	void EndBenchmark();
	int GetFrameRate();

	void SetDebugMode(bool newDebugMode);
	void SetDebugModeNoCollision(bool newDebugModeNoCollision);
	void SetDebugModeCollisionTest(bool newDebugModeCollisionTest);
	bool GetDebugMode();
	bool GetDebugModeNoCollision();
	bool GetDebugModeCollisionTest();

private:
	void DisplayBenchmark();
	void CalculateFrameRate();
	int mFrameRate;
	Timer* mDebugTimer;

	bool mDebugMode;
	bool mDebugModeNoCollision;
	bool mDebugModeCollisionTest;
};

#endif /* DEBUG_H_ */
