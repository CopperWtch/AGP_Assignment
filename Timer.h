/**
AGP Assignment
Timer.h
Purpose: Header file for Timer.cpp

@author Sarah Bulk
*/

#pragma once
#ifndef _TIMER_H_
#define _TIMER_H_

#include <windows.h>
#include "AGPSideScroller.h"

class Timer
{
private:
	static Timer* mTimerInstance;

	float mTicksPerS;
	LONGLONG mStart;
	float mTotalTime;
	float mElapsedTime;

	// To manage the ability to pause the time of the game
	bool mBIsPaused;

	// Methods
	Timer() { }
	Timer(const Timer&) { }
	Timer& operator=(const Timer&) { return *this; }

public:
	// Destructor
	virtual ~Timer() { }

	static Timer* getInstance();

	HRESULT initialize();
	HRESULT update();
	HRESULT shutdown();

	//--ACCESS MODIFIERS--//

	float GetTotalGameTime();

	// Pausing functionality
	void PauseTime(bool a_bOn);
	bool TogglePause();
	bool GetIsPaused();

};

#endif