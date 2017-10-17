#include <iostream>
#include <string>

#include "Engine.h"
#include "GameObject.h"

bool lol = false;
GameObject* go;
GameObject* goBis;

Engine::Engine()
{
	Launch();
}

Engine::~Engine()
{
	/*if(go != nullptr)
		go->Destroy();
	if (goBis != nullptr)
		goBis->Destroy();*/
}

void Engine::Launch()
{
	_isRunning = true;
	_window->Init();

	goBis = new GameObject("BeforeStart", false);

	_debug->SetDebugWindow(_window->GetDebugWindowLayout());

	_debug->Print("lol");

	_objectManager->StartAllEngineObjects();
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

	_debug->SaveLog();
	delete _input;
	delete _window;
	delete _time;
	delete _objectManager;
	delete _garbageCollector;
	delete _debug;
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

void Engine::Update(float deltaTime)
{
	if (_currentTimeForInput < _timeBeforeInput)
	{
		_currentTimeForInput += deltaTime;
		if (_currentTimeForInput >= _timeBeforeInput)
		{
			_input->SetCanInput(true);
		}
	}

	if (_input->GetKeyPressed(KEY::SPACE))
	{
		if (lol == false)
		{
			lol = true;
			go = new GameObject(std::string("ObjectUpdate"));
		}
	}

	if (_input->GetKeyPressed(KEY::A))
	{
		if (go != nullptr)
		{
			go->Destroy();
			go = nullptr;
			lol = false;
		}
	}
}