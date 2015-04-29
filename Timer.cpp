/**
AGP Assignment
Timer.cpp
Purpose: A Timer for the game

@author Sarah Bulk
*/

#include "Timer.h"

Timer* Timer::mTimerInstance = NULL;

//////////////////////////////////////////////////////////////////////////////////////
// Return the timer instance
//////////////////////////////////////////////////////////////////////////////////////
Timer* Timer::getInstance()
{
	if (!mTimerInstance)
	{
		mTimerInstance = new Timer();
	}

	return mTimerInstance;
}

//////////////////////////////////////////////////////////////////////////////////////
// Initialize the timer
//////////////////////////////////////////////////////////////////////////////////////
HRESULT Timer::initialize()
{

	LARGE_INTEGER i;
	if (!QueryPerformanceFrequency(&i))
		return false;
	mTicksPerS = (float)(i.QuadPart);

	QueryPerformanceCounter(&i);
	mStart = i.QuadPart;
	mTotalTime = 0;
	mElapsedTime = 0;

	// Reset pausing
	mBIsPaused = false;

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////////////
// Update the timer to reflect the total time
//////////////////////////////////////////////////////////////////////////////////////
HRESULT Timer::update()
{

	LARGE_INTEGER i;
	QueryPerformanceCounter(&i);
	mElapsedTime = (float)(i.QuadPart - mStart) / mTicksPerS;
	mStart = i.QuadPart;

	//update the total time only if the timer isn't currently paused
	if (!mBIsPaused)
	{
		mTotalTime += mElapsedTime;
	}

	return S_OK;
}

HRESULT Timer::shutdown()
{
	// Check if we created the instance
	if (mTimerInstance)
	{
		delete mTimerInstance;
		mTimerInstance = NULL;
	}

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////////////
// Access modifiers
//////////////////////////////////////////////////////////////////////////////////////

float Timer::GetTotalGameTime()
{
	return mTotalTime;
}

void Timer::PauseTime(bool a_bOn) {
	mBIsPaused = a_bOn;

}
bool Timer::TogglePause() {
	mBIsPaused ^= true;

	return mBIsPaused;
}
bool Timer::GetIsPaused() {
	return mBIsPaused;
}
