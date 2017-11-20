#include <iostream>
#include <string>

#include "Engine.h"
#include "Menu.h"

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

	_sceneManager->LoadScenesFromFile();

	_sceneManager->NewScene(new Menu());

	//TESTFUNCTION();
	
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

	_window->Update(deltaTime);

	if (_input->GetKeyDown(KEYCODE::F1) && !ISRELEASE)
	{
		_window->ToggleConsole();
	}
}

void Engine::Render()
{
	_objectManager->RenderAllEngineObjects(_window->GetWindow());
	_sceneManager->RenderCurrentScene(_window->GetWindow());
}

#include "GameObject.h"
#include "SpriteRenderer.h"
#include "Scene.h"
#include "InputLeaf.h"
#include "SpriteAnimator.h"
#include "FMath.h"

void Engine::TESTFUNCTION()
{
	_sceneManager->NewScene("TestScene");
	if (_sceneManager->GetCurrentScene() == nullptr)
	{
		_sceneManager->LoadScene("TestScene");
	}

	GameObject* go = new GameObject("go");

	GameObject* background = new GameObject("background");
	GameObject* foreground = new GameObject("foreground");

	go->transform.position = FVector3(60, 520, 1);
	go->transform.scale = FVector3(.75f, .75f, .75f);
	background->transform.position = FVector3(0, -300, 3);
	foreground->transform.position = FVector3(0, -300, 0);

	SpriteRenderer* sr = new SpriteRenderer();
	sr->Init("Sprites/testSprite.png");
	go->AddLeaf(sr);
	InputLeaf* inputL = new InputLeaf();
	go->AddLeaf(inputL);

	SpriteRenderer* sr3 = new SpriteRenderer();
	sr3->Init("Sprites/Background_01/PARALLAX/background.png");
	SpriteRenderer* sr4 = new SpriteRenderer();
	sr4->Init("Sprites/Background_01/PARALLAX/clouds.png");
	SpriteRenderer* sr5 = new SpriteRenderer();
	sr5->Init("Sprites/Background_01/PARALLAX/rocks.png");
	background->AddLeaf(sr3);
	background->AddLeaf(sr4);
	background->AddLeaf(sr5);

	SpriteRenderer* sr6 = new SpriteRenderer();
	sr6->Init("Sprites/Background_01/PARALLAX/trees.png");
	foreground->AddLeaf(sr6);

	_sceneManager->GetCurrentScene()->AddDynamicObjectToScene(go);
	_sceneManager->GetCurrentScene()->AddDynamicObjectToScene(foreground);

	_sceneManager->GetCurrentScene()->AddStaticObjectToScene(background);

}