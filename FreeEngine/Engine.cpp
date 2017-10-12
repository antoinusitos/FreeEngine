#include <iostream>

#include "Engine.h"
#include "GameObject.h"

Engine::Engine()
{
	Launch();
}

Engine::~Engine()
{

}

void Engine::Launch()
{
	_isRunning = true;
	_window->Init();

	while (_isRunning)
	{
		// Update the time of the engine
		_time->Update();

		// Handle the events to close the engine
		CheckMustCloseWindow();

		// Put engine stuff here
		Update(_time->deltaTime);

		_objectManager->UpdateAllEngineObjects(_time->deltaTime);
		_objectManager->RenderAllEngineObjects();

		_window->Render();
	}
}

void Engine::CheckMustCloseWindow()
{
	// Gather the inputs for the engine
	_input->ProcessInput(*_window->GetWindow());

	// Close the window if escape is pressed
	if (_input->GetKeyPressed(KEY::ESCAPE) || _input->MustClose())
	{
		_window->Exit();
		_isRunning = false;
	}
}

bool lol = false;
GameObject* go;

void Engine::Update(float deltaTime)
{
	if (_input->GetKeyPressed(KEY::SPACE))
	{
		std::cout << "Space Pressed" << std::endl;
		if (lol == false)
		{
			lol = true;
			go = new GameObject();
		}
	}
}