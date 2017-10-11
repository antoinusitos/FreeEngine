#include <iostream>

#include "Engine.h"
#include "Input.h"
#include "Window.h"

Engine::Engine()
{
	Launch();
}

Engine::~Engine()
{

}

void Engine::Update()
{
	if (Input::GetInstance().GetKeyPressed(KEY::SPACE))
	{
		std::cout << "Space Pressed" << std::endl;
	}
}

void Engine::Launch()
{
	_isRunning = true;
	Window::GetInstance().Init();
	while (_isRunning)
	{
		Input::GetInstance().ProcessInput(*Window::GetInstance().GetWindow());

		// Close the window if escape is pressed
		if (Input::GetInstance().GetKeyPressed(KEY::ESCAPE))
		{
			Window::GetInstance().Exit();
			_isRunning = false;
		}

		Update(); // add the delta time with a time manager
	}
}