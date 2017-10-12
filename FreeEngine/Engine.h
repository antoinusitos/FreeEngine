#pragma once

#include "Input.h"
#include "Window.h"
#include "Time.h"

class Engine
{
public:
	Engine();
	~Engine();

	void Update();

	// Launch the engine and init every classes
	void Launch();

private :
	// Control the end of the engine
	bool _isRunning = false;

	Input _input = *Input::GetInstance();
	Window _window = *Window::GetInstance();
	Time _time = *Time::GetInstance();
};

