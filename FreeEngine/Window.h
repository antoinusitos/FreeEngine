#pragma once

#include <SFML/Graphics.hpp>

#include <memory>
#include <mutex>
#include <iostream>

class DebugWindowLayout;
class WindowLayout;

class Window
{
public:
	// Constructor
	Window();
	//Destructor
	~Window();

	// Get a unique instance of the time
	static Window& Window::Instance()
	{
		std::call_once(Window::onceFlag, []() {
			_instance.reset(new Window);
		});

		std::cout << "Getting  Window instance" << '\n';
		return *(_instance.get());
	}

	// Get the SFML window
	std::shared_ptr<sf::RenderWindow> GetWindow();

	// Init the class
	std::shared_ptr<sf::RenderWindow> Init();

	void InitInternalWindows();

	// Close the window
	void Exit();

	// Render the Window
	void Render();

	void AddRenderingLayout(WindowLayout* newLayout);

	DebugWindowLayout* GetDebugWindowLayout();

private :
	// Unique instance of the time
	static std::unique_ptr<Window> _instance;
	static std::once_flag onceFlag;

	// Instance of the SFML window
	std::shared_ptr<sf::RenderWindow> _window;

	std::vector<WindowLayout*> _allWindowLayout;

	DebugWindowLayout* dwl = nullptr;
};

