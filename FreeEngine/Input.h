#pragma once

#include <SFML/Window.hpp>
#include <map> 

enum KEY
{
	SPACE,
	ESCAPE,
	ARROWUP,
	ARROWDOWN,
	ARROWRIGHT,
	ARROWLEFT,
};

class Input
{
public:
	// Constructor
	Input();
	//Destructor
	~Input();

	// Get a unique instance of the time
	static Input* GetInstance()
	{
		if (NULL == _instance)
		{
			_instance = new Input;
		}

		return _instance;
	}

	// Process the input related to the engine
	void ProcessInput(sf::Window& window);

	// Check if the key is pressed
	bool GetKeyPressed(KEY key);

	// Check if we must close the window
	bool MustClose();

private :

	// Object that gather the events in the SFML window
	sf::Event _event;

	// Unique instance of the time
	static Input* _instance;	

	// Map that contain the state of the Input
	std::map<KEY, bool> _mapping;

	// Should we close the SFML window ?
	bool _mustClose = false;
};


