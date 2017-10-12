#include "Time.h"
#include <iostream>

Time* Time::_instance = NULL;

Time::Time()
{
	// Init all the variable
	timeElapsed = 0;
	deltaTime = 0;
	lastTimeElapsed = 0;
}

Time::~Time()
{
}

void Time::Update()
{
	// Get current time
	_currentTime = clock();

	// Calculate the time elapsed in seconds
	timeElapsed = (double)_currentTime / CLOCKS_PER_SEC;
	// Calculate the time elapsed since last frame
	deltaTime = timeElapsed - lastTimeElapsed;

	// Stock the current time for the delta time
	lastTimeElapsed = timeElapsed;
}