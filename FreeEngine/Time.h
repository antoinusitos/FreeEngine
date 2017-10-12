#pragma once
#define NULL 0

#include <time.h> 

class Time
{
public:
	// Constructor
	Time();
	//Destructor
	~Time();

	// Get a unique instance of the time
	static Time* GetInstance()
	{
		if (NULL == _instance)
		{
			_instance = new Time;
		}

		return _instance;
	}

	// Update the time in the engine
	void Update();

	// Time elapsed since the beginning of the engine
	double timeElapsed;
	// Time elapsed since the last frame
	double deltaTime;

private:
	// Unique instance of the time
	static Time* _instance;

	// Current Time according to Computer time
	clock_t _currentTime;
	// Time elapsed at the last frame
	double lastTimeElapsed;

};

