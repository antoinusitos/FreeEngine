#pragma once
#define NULL 0

#include <time.h> 
#include <memory>
#include <mutex>
#include <iostream>

const int FPSMAX = 60;

class Time
{
public:
	// Constructor
	Time();
	//Destructor
	~Time();

	// Get a unique instance of the time
	static Time& Time::Instance()
	{
		std::call_once(Time::onceFlag, []() {
			_instance.reset(new Time);
		});

		return *(_instance.get());
	}

	void Init();

	// Update the time in the engine
	void Update();

	// Time elapsed since the beginning of the engine
	float timeElapsed;
	// Time elapsed since the last frame
	float deltaTime;

	const std::string GetCurrentTimeAsString();

private:
	// Unique instance of the time
	static std::unique_ptr<Time> _instance;
	static std::once_flag onceFlag;

	// Current Time according to Computer time
	clock_t _currentTime;
	// Time elapsed at the last frame
	float lastTimeElapsed;

	float _timeLastFrame = 0;

	int _currentFps = 0;

};

