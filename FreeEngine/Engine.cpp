#include <iostream>
#include <string>

#include "Engine.h"
#include "Menu.h"
#include "TestScene.h"

Engine::Engine()
{
	_debug = &Debug::Instance(); // keep it up to record and print everything
	_editorManager = &EditorManager::Instance();
	_data = &Data::Instance();
	_input = &Input::Instance();
	_window = &Window::Instance();
	_time = &Time::Instance();
	_objectManager = &ObjectsManager::Instance();
	_fileHandler = &FileHandler::Instance();
	_resourcesManager = &ResourcesManager::Instance();
	_globalListener = &GlobalListener::Instance();
	_gamepadManager = &GamepadManager::Instance();
	_cameraManager = &CameraManager::Instance();
	_math = &FMath::Instance();
	_saveManager = &SaveManager::Instance();
	_sceneManager = &SceneManager::Instance();

	Launch();
}

Engine::~Engine()
{

}

void Engine::NotifyChange()
{
	_debug->Log("Engine observer file changed !", DebugMessageType::DEBUGENGINE);
}

void Engine::Launch()
{
	_debug->Log("Launching Engine...", DebugMessageType::DEBUGENGINE);

	_isRunning = true;
	
	_input->Init();

	_window->Init();

	_fileHandler->UpdateWatchers(_time->deltaTime);

	_cameraManager->Init();

	_window->SetView(_cameraManager->GetView());

	_window->InitInternalWindows();

	_gamepadManager->Init();

	_time->Init();

	//_sceneManager->LoadScenesFromFile();

	_sceneManager->NewScene(new TestScene());
	_sceneManager->NewScene(new Menu());
	
	_debug->Log("Engine Init !", DebugMessageType::DEBUGENGINE);


	_sceneManager->PreAwakeCurrentScene();
	_objectManager->AwakeAllEngineObjects();
	_sceneManager->AwakeCurrentScene();
	_objectManager->StartAllEngineObjects();
	_sceneManager->StartCurrentScene();

	while (_isRunning)
	{
		// Update the time of the engine
		_time->Update();

		// Handle the events to close the engine
		CheckMustCloseWindow();

		_window->ClearWindow();

		// Put engine stuff here
		Update(_time->deltaTime);

		// Render scene and other stuff
		Render();

		// Render every thing
		_window->Render();

		_window->DisplayWindow();

		// update inputs
		_input->Update(_time->deltaTime);
	}

	_sceneManager->SaveScenesInFile();
	_window->RemoveAllRendering();
	_debug->SaveLog();
}

void Engine::CheckMustCloseWindow()
{
	// Gather the inputs for the engine
	_input->ProcessInput(*_window->GetWindow());

	// Close the window if escape is pressed
	if (_input->GetKeyPressed(KEYCODE::ESCAPE) || _editorManager->GetMustQuit())
	{
		_debug->Log("Shutting Down Engine...", DebugMessageType::DEBUGENGINE);
		_window->Exit();
		_isRunning = false;
	}
}

void Engine::Update(const float deltaTime)
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
	_sceneManager->UpdateCurrentScene(deltaTime);

	_input->SaveMousePos(*_window->GetWindow());

	_cameraManager->Update(deltaTime);

	_window->Update(deltaTime);

	if (_input->GetKeyDown(KEYCODE::F1) && !ISRELEASE)
	{
		_window->ToggleConsole();
	}

	if (_input->GetKeyDown(KEYCODE::F2) && !ISRELEASE)
	{
		_editorManager->ChangeCurrentState();
	}
}

void Engine::Render()
{
	_objectManager->RenderAllEngineObjects(_window->GetWindow());
	_sceneManager->RenderCurrentScene(_window->GetWindow());

	// do this at the end for the post process
	_cameraManager->Render(_window->GetWindow());
}