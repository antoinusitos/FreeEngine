#include <iostream>
#include <string>

#include "Engine.h"
#include "GameObject.h"

bool lol = false;
GameObject* go;
GameObject* goBis;

Engine::Engine()
{
	_debug = &Debug::Instance(); // keep it up to record and print everything
	_input = &Input::Instance();
	_window = &Window::Instance();
	_time = &Time::Instance();
	_objectManager = &ObjectsManager::Instance();
	_garbageCollector = &GarbageCollector::Instance();
	_fileHandler = &FileHandler::Instance();
	Launch();
}

Engine::~Engine()
{

}

void Engine::NotifyChange()
{
	std::cout << "lol" << '\n';
}

void Engine::Launch()
{
	_isRunning = true;
	
	_input->Init();

	_window->Init();
	_window->InitInternalWindows();

	goBis = new GameObject("BeforeStart", false);
	goBis->RegisterInObjectManager();

	_debug->SetDebugWindow(_window->GetDebugWindowLayout());

	_fileHandler->RegisterNewWatcher(this, "D:/Test.txt");

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

	_window->RemoveAllRendering();
	_debug->SaveLog();
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

	_fileHandler->UpdateWatchers(_time->deltaTime);

	if (_input->GetKeyPressed(KEY::SPACE))
	{
		if (lol == false)
		{
			lol = true;
			go = new GameObject(std::string("ObjectUpdate"));
			go->RegisterInObjectManager();
		}
	}

	if (_input->GetKeyPressed(KEY::A))
	{
		if (go != nullptr)
		{
			go->Destroy();
			delete go;
			go = nullptr;
			lol = false;
		}
	}
}