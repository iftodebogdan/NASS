/*
 * Debug.cpp
 *
 *  Created on: Jun 8, 2013
 *      Author: Bogdan
 */

#include "../Includes/Debug.hpp"

#include "../Includes/Resources.hpp"

Debug::Debug()
{
	mFrameRate = 60;
	mDebugTimer = new Timer();

	SetDebugMode(false);
	SetDebugModeCollisionTest(false);
	SetDebugModeNoCollision(false);
}

Debug::~Debug()
{
	delete mDebugTimer;
}

void Debug::DebugScreen()
{
	CalculateFrameRate();

	oslSetBkColor(COLOR_BLACK);
	oslSetTextColor(COLOR_WHITE);

	DisplayBenchmark();
	oslPrintf("FPS: %d\n", GetFrameRate());
	oslPrintf("RAM free: %f KB\n", (float)oslGetRamStatus().maxAvailable / 1024);
	/*
	oslPrintf("Enemy count: %d\n", Resources::mEnemyList->GetEnemyCount());
	oslPrintf("Available audio channels: ");
	for(int i=0;i<=7;i++)
		if(Audio::IsChannelAvailable(i))
			oslPrintf("%i ", i);
	oslPrintf("\n");
	*/
	oslPrintf("No collision: %s\n", GetDebugModeNoCollision() ? "true" : "false");
	oslPrintf("Collision test: %s\n", GetDebugModeCollisionTest() ? "true" : "false");

	if(Resources::mController->IsPressed(Controller::L))
		SetDebugModeNoCollision(!GetDebugModeNoCollision());

	if(Resources::mController->IsPressed(Controller::R))
		SetDebugModeCollisionTest(!GetDebugModeCollisionTest());
}

int Debug::GetFrameRate()
{
	if(mFrameRate)
		return mFrameRate;
	else
		return 1;
}

void Debug::CalculateFrameRate()
{
	mFrameRate = (float)1000 / (float)mDebugTimer->getStartTimeMs();
	mDebugTimer->ResetStartTime();
}

void Debug::InitBenchmark()
{
	oslBenchmarkTest(OSL_BENCH_INIT);
}

void Debug::StartBenckmark()
{
	oslBenchmarkTest(OSL_BENCH_START);
}

void Debug::EndBenchmark()
{
	oslBenchmarkTest(OSL_BENCH_END);
}

void Debug::DisplayBenchmark()
{
	oslSysBenchmarkDisplay();
	oslPrintf("\n");
}

void Debug::SetDebugMode(bool newDebugMode)
{
	mDebugMode = newDebugMode;
}

void Debug::SetDebugModeNoCollision(bool newDebugModeNoCollision)
{
	mDebugModeNoCollision = newDebugModeNoCollision;
}

void Debug::SetDebugModeCollisionTest(bool newDebugModeCollisionTest)
{
	mDebugModeCollisionTest = newDebugModeCollisionTest;
}

bool Debug::GetDebugMode()
{
	return mDebugMode;
}

bool Debug::GetDebugModeNoCollision()
{
	return mDebugModeNoCollision;
}

bool Debug::GetDebugModeCollisionTest()
{
	return mDebugModeCollisionTest;
}
