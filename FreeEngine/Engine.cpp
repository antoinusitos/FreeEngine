#include <iostream>
#include <string>

#include "Engine.h"

//-------------TEST-------------
#include "GameObject.h"
#include "Sound.h"
bool lol = false;
GameObject* go;
GameObject* goBis;
Sound* s;
Sound* sbis;
//-------------TEST-------------

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

	goBis = new GameObject("BeforeStart", false);
	goBis->RegisterInObjectManager();

	_objectManager->StartAllEngineObjects();


	//-------------TEST-------------
	s = new Sound();
	s->InitMusic("theme.wav");
	//s->Play();
	//-------------TEST-------------

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

	_fileHandler->UpdateWatchers(_time->deltaTime);


	//-------------TEST-------------
	if (_input->GetKeyDown(KEYCODE::SPACE))
	{
		if (lol == false)
		{
			lol = true;
			go = new GameObject(std::string("ObjectUpdate"));
			go->RegisterInObjectManager();
			sbis = new Sound();
			sbis->InitSound("ouverture.wav");
			sbis->SetDistance(5, 10);
			sbis->SetPosition(0, 0, 5);
			sbis->SetLoop(true);
			sbis->Play();
		}
	}

	if (_input->GetKeyDown(KEYCODE::A))
	{
		if (go != nullptr)
		{
			go->Destroy();
			delete go;
			go = nullptr;
			lol = false;
		}
	}
	//-------------TEST-------------
}