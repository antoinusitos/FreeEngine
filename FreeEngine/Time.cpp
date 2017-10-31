#include "Time.h"
#include <iostream>

std::unique_ptr<Time> Time::_instance;
std::once_flag Time::onceFlag;

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
	timeElapsed = (float)_currentTime / CLOCKS_PER_SEC;
	// Calculate the time elapsed since last frame
	deltaTime = timeElapsed - lastTimeElapsed;

	// Stock the current time for the delta time
	lastTimeElapsed = timeElapsed;
}

std::string Time::GetCurrentTimeAsString()
{
	time_t rawtime;
	struct tm timeinfo;
	char buffer[80];

	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);

	strftime(buffer, sizeof(buffer), "%d-%m-%Y_%I-%M-%S", &timeinfo);
	std::string str(buffer);
	return str;
}