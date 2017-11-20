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
	const bool GetKeyDown(const KEYCODE key);

	// Check if the key is pressed
	const bool GetKeyPressed(const KEYCODE key);

	// Check if the key is just released
	const bool GetKeyReleased(const KEYCODE key);

	void SetCanInput(const bool NewState);

	void Init();

	void Update(const float deltaTime);

	void SaveMousePos(const sf::Window& window);

	const FVector2 GetMousePosition();

private :

	// Object that gather the events in the SFML window
	sf::Event _event;

	// Unique instance of the time
	static std::unique_ptr<Input> _instance;
	static std::once_flag onceFlag;

	// Map that contain the state of the Input
	std::map<KEYCODE, InputKey> _mapping;

	bool _canInput = false;

	const KEYCODE GetKeycodeAssociate(const sf::Keyboard::Key key);
	const KEYCODE GetMouseCodeAssociate(const sf::Mouse::Button button);

	FVector2 _mousePosition;
};


