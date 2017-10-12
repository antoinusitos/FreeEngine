#pragma once

#include "Input.h"
#include "Window.h"
#include "Time.h"
#include "ObjectsManager.h"

class Engine
{
public:
	Engine();
	~Engine();

	void Update(float deltaTime);

	// Launch the engine and init every classes
	void Launch();

	// Handle the events to close the engine
	void CheckMustCloseWindow();

private :
	// Control the end of the engine
	bool _isRunning = false;

	Input* _input = Input::GetInstance();
	Window* _window = Window::GetInstance();
	Time* _time = Time::GetInstance();
	ObjectsManager* _objectManager = ObjectsManager::GetInstance();
};

