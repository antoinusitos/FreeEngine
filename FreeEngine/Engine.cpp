#include <iostream>
#include <string>

#include "Engine.h"
#include "GameObject.h"

bool lol = false;
GameObject* go;

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

	GameObject* goBis = new GameObject("BeforeStart", false);

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

	delete goBis;
	delete go;
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
	if (_input->GetKeyPressed(KEY::SPACE))
	{
		//std::cout << "Space Pressed" << std::endl;
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
			delete go;
			go = nullptr;
			lol = false;
		}
	}
}