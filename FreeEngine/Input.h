#pragma once

#include <SFML/Window.hpp>
#include <map> 
#include <memory>
#include <mutex>
#include <iostream>

#include "Data.h"

#include "FVector2.h"

class Input
{
public:
	// Constructor
	Input();
	//Destructor
	~Input();

	// Get a unique instance of the time
	static Input& Input::Instance()
	{
		std::call_once(Input::onceFlag, []() {
			_instance.reset(new Input);
			//std::cout << "Getting  Input instance" << '\n';
		});

		return *(_instance.get());
	}

	// Process the input related to the engine
	void ProcessInput(sf::Window& window);

	// Check if the key was just pressed
	bool GetKeyDown(KEYCODE key);

	// Check if the key is pressed
	bool GetKeyPressed(KEYCODE key);

	// Check if the key is just released
	bool GetKeyReleased(KEYCODE key);

	// Check if we must close the window
	bool MustClose();

	void SetCanInput(bool NewState);

	void Init();

	void Update(float deltaTime);

	void SaveMousePos(sf::Window& window);

	FVector2 GetMousePosition();

private :

	// Object that gather the events in the SFML window
	sf::Event _event;

	// Unique instance of the time
	static std::unique_ptr<Input> _instance;
	static std::once_flag onceFlag;

	// Map that contain the state of the Input
	std::map<KEYCODE, InputKey> _mapping;

	// Should we close the SFML window ?
	bool _mustClose = false;

	bool _canInput = false;

	KEYCODE GetKeycodeAssociate(sf::Keyboard::Key key);
	KEYCODE GetMouseCodeAssociate(sf::Mouse::Button button);

	FVector2 _mousePosition;
};


