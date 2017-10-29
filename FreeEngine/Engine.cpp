#include <iostream>
#include <string>

#include "Engine.h"

#include "Vector3.h"

#include "GameObject.h"
#include "TestLeaf.h"

GameObject* go;

Engine::Engine()
{
	_debug = &Debug::Instance(); // keep it up to record and print everything
	_data = &Data::Instance();
	_input = &Input::Instance();
	_window = &Window::Instance();
	_time = &Time::Instance();
	_objectManager = &ObjectsManager::Instance();
	_fileHandler = &FileHandler::Instance();
	_resourcesManager = &ResourcesManager::Instance();
	_globalListener = &GlobalListener::Instance();
	_gamepadManager = &GamepadManager::Instance();
	_cameradManager = &CameraManager::Instance();

	Launch();
}

Engine::~Engine()
{

}

void Engine::NotifyChange()
{
	std::cout << "file changed !" << '\n';
}

void Engine::Launch()
{
	_isRunning = true;
	
	_input->Init();

	_window->Init();

	_window->SetView(_cameradManager->GetView());

	_window->InitInternalWindows();

	_gamepadManager->Init();

	go = new GameObject("go");
	TestLeaf* l = new TestLeaf();
	go->AddLeaf(l);
	_objectManager->RegisterEngineObject(go);

	_objectManager->AwakeAllEngineObjects();
	_objectManager->StartAllEngineObjects();

	while (_isRunning)
	{
		// Update the time of the engine
		_time->Update();

		// Handle the events to close the engine
		CheckMustCloseWindow();

		// Put engine stuff here
		Update(_time->deltaTime);

		// Render every thing
		_window->Render();

		// update inputs
		_input->Update(_time->deltaTime);
	}

	_window->RemoveAllRendering();
	_debug->SaveLog();
}

void Engine::CheckMustCloseWindow()
{
	// Gather the inputs for the engine
	_input->ProcessInput(*_window->GetWindow());

	// Close the window if escape is pressed
	if (_input->GetKeyPressed(KEYCODE::ESCAPE) || _input->MustClose())
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

	_fileHandler->UpdateWatchers(deltaTime);

	_gamepadManager->Update(deltaTime);

	_objectManager->UpdateAllEngineObjects(_time->deltaTime);
	_objectManager->RenderAllEngineObjects();

}