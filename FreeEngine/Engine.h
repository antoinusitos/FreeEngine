#pragma once

#include "Input.h"
#include "Window.h"
#include "Time.h"
#include "ObjectsManager.h"
#include "Debug.h"
#include "FileHandler.h"
#include "Data.h"
#include "ResourcesManager.h"
#include "GlobalListener.h"
#include "GamepadManager.h"
#include "CameraManager.h"
#include "EditorManager.h"
#include "FMath.h"

class Engine : public FileObserver
{
public:
	Engine();
	~Engine();

	void Update(const float deltaTime);

	// Launch the engine and init every classes
	void Launch();

	// Handle the events to close the engine
	void CheckMustCloseWindow();

	sf::RenderWindow* sp;

	//TEST
	void NotifyChange();

private :
	// Control the end of the engine
	bool _isRunning = false;

	Data* _data;
	Input* _input;
	Window* _window;
	Time* _time;
	ObjectsManager* _objectManager;
	Debug* _debug;
	FileHandler* _fileHandler;
	ResourcesManager* _resourcesManager;
	GlobalListener* _globalListener;
	GamepadManager* _gamepadManager;
	CameraManager* _cameraManager;
	EditorManager* _editorManager;
	FMath* _math;

	float _timeBeforeInput = 2.0f;
	float _currentTimeForInput = 0.0f;

};

