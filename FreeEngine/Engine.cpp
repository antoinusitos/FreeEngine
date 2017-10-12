#include <iostream>

#include "Engine.h"

Engine::Engine()
{
	Launch();
}

Engine::~Engine()
{

}

void Engine::Update()
{
	if (_input.GetKeyPressed(KEY::SPACE))
	{
		std::cout << "Space Pressed" << std::endl;
	}
}

void Engine::Launch()
{
	_isRunning = true;
	_window.Init();

	while (_isRunning)
	{
		// Update the time of the engine
		_time.Update();

		// Gather the inputs for the engine
		_input.ProcessInput(*_window.GetWindow());

		// Close the window if escape is pressed
		if (_input.GetKeyPressed(KEY::ESCAPE) || _input.MustClose())
		{
			_window.Exit();
			_isRunning = false;
		}

		// Put engine stuff here
		Update();
	}
}