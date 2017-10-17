#pragma once

#include "Input.h"
#include "Window.h"
#include "Time.h"
#include "ObjectsManager.h"
#include "GarbageCollector.h"
#include "Debug.h"

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

	std::shared_ptr<sf::RenderWindow> sp;
private :
	// Control the end of the engine
	bool _isRunning = false;

	Input _input;
	Window _window;
	Time _time;
	ObjectsManager _objectManager;
	GarbageCollector _garbageCollector;
	Debug _debug;

	float _timeBeforeInput = 2.0f;
	float _currentTimeForInput = 0.0f;

};

