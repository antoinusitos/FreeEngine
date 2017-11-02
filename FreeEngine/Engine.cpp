#include <iostream>
#include <string>

#include "Engine.h"

#include "Vector3.h"

//-----TEST-----
#include "GameObject.h"
#include "TestLeaf.h"
#include "SpriteRenderer.h"
#include "SpriteAnimator.h"

GameObject* go;
SpriteAnimator* sr;
float speed = 1;


#include "Animator.h"
#include "State.h"
#include "Transition.h"

Animator* anim;
State* s1;
State* s2;
SpriteAnimator* sr2;

//-----TEST-----

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
	_cameraManager = &CameraManager::Instance();

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

	_fileHandler->UpdateWatchers(_time->deltaTime);

	_cameraManager->Init();

	_window->SetView(_cameraManager->GetView());

	_window->InitInternalWindows();

	_gamepadManager->Init();

	//-----TEST-----
	go = new GameObject("go");
	//SpriteRenderer* sr = new SpriteRenderer();
	//sr->Init("Sprites/zelda/frame0.png");
	//go->AddLeaf(sr);
	/*sr = new SpriteAnimator();
	for (int i = 0; i < 8; i++)
	{
		sr->AddTexture("Sprites/zelda/frame" + std::to_string(i) + ".png");
	}
	go->AddLeaf(sr);
	go->transform.position.x = 100;
	go->transform.position.y = 100;*/


	anim = new Animator();
	s1 = new State("s1");
	s2 = new State("s2");

	sr = new SpriteAnimator();
	for (int i = 0; i < 8; i++)
	{
		sr->AddTexture("Sprites/zelda/frame" + std::to_string(i) + ".png");
	}

	sr2 = new SpriteAnimator();
	sr2->AddTexture("Sprites/zelda/frame0.png");

	s1->SetSpriteAnimator(sr);
	s2->SetSpriteAnimator(sr2);

	Transition* t = new Transition();
	t->condition.name = "testBool";
	t->condition.type = 0;
	t->condition.conditiontype.b_return = true;

	Transition* t2 = new Transition();
	t2->condition.name = "testInt";
	t2->condition.type = 1;
	t2->condition.conditiontype.i_return = 10;

	s1->SetTransition(s2, t);
	s2->SetTransition(s1, t2);

	anim->AddNewState(s1);
	anim->AddNewState(s2);

	go->AddLeaf(anim);

	//-----TEST-----

	_objectManager->AwakeAllEngineObjects();
	_objectManager->StartAllEngineObjects();

	_time->Init();

	while (_isRunning)
	{
		// Update the time of the engine
		_time->Update();

		// Handle the events to close the engine
		CheckMustCloseWindow();

		_window->ClearWindow();

		// Put engine stuff here
		Update(_time->deltaTime);

		// Render every thing
		_window->Render();

		_window->DisplayWindow();

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
	_objectManager->RenderAllEngineObjects(_window->GetWindow());

	if (_input->GetKeyDown(KEYCODE::F1))
	{
		_window->ToggleConsole();
	}

	//-----TEST-----
	if (_input->GetKeyDown(KEYCODE::A))
	{
		anim->SetBool("testBool", true);
	}
	if (_input->GetKeyDown(KEYCODE::B))
	{
		anim->SetInt("testInt", 9);
	}
	if (_input->GetKeyDown(KEYCODE::C))
	{
		anim->SetInt("testInt", 10);
	}
	//-----TEST-----

}