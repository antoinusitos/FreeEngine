#pragma once

#include <SFML/Graphics.hpp>

#include <memory>
#include <mutex>
#include <iostream>

#include "FileHandler.h"
#include "Data.h"

class DebugWindowLayout;
class ToolBar;
class WindowLayout;

class Window : public FileObserver
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
			//std::cout << "Getting  Window instance" << '\n';
		});

		return *(_instance.get());
	}

	// Get the SFML window
	sf::RenderWindow* GetWindow();

	// Init the class
	void Init();

	void InitInternalWindows();

	// Close the window
	void Exit();

	// Render the Window
	void Render();
	
	void Update(const float deltaTime);

	void AddRenderingLayout(WindowLayout* newLayout);
	void RemoveRenderingLayout(WindowLayout* layoutToRemove);

	DebugWindowLayout* GetDebugWindowLayout();
	const ToolBar* GetToolBar();

	void RemoveAllRendering();

	void NotifyChange();
	
	const unsigned int GetScreenResolutionX();
	const unsigned int GetScreenResolutionY();

	void SetView(const sf::View newView);

	void ResetToDefaultView();

	void ToggleConsole();

	void ClearWindow();
	void DisplayWindow();

//Variables
private :
	// Unique instance of the time
	static std::unique_ptr<Window> _instance;
	static std::once_flag onceFlag;

	// Instance of the SFML window
	std::unique_ptr<sf::RenderWindow> _window;

	std::vector<WindowLayout*> _allWindowLayout;

	std::unique_ptr<DebugWindowLayout> _console;

	std::unique_ptr<ToolBar> _toolbar;

	std::string configFileName = "Assets/Config/Engine.txt";

	std::vector<EngineData> _allEngineData;

	ScreenType _screenType;

	unsigned int _screenResolutionX;
	unsigned int _screenResolutionY;

	bool _showingConsole = false;

//Functions
private:
	void HandleDataChanges();

	void SetResolutionScreen(const int X, const int Y, const int posX, const int posY);

	void SetScreenType(const ScreenType newType);

	void GetResolutionValuesWithDelimiter(std::string& text, const std::string delimiter, std::string& x, std::string& y);
};

