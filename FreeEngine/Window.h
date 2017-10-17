#pragma once

#include <SFML/Graphics.hpp>

#include "WindowLayout.h"

class DebugWindowLayout;

class Window
{
public:
	// Constructor
	Window();
	//Destructor
	~Window();

	// Get a unique instance of the time
	static Window* GetInstance()
	{
		if (NULL == _instance)
		{
			_instance = new Window;
		}

		return _instance;
	}

	// Get the SFML window
	sf::RenderWindow* GetWindow();

	// Init the class
	void Init();

	// Close the window
	void Exit();

	// Render the Window
	void Render();

	void AddRenderingLayout(WindowLayout* newLayout);

	DebugWindowLayout* GetDebugWindowLayout();

private :
	// Unique instance of the time
	static Window* _instance;

	// Instance of the SFML window
	sf::RenderWindow* _window;

	std::vector<WindowLayout*> _allWindowLayout;

	DebugWindowLayout* dwl = nullptr;
};

