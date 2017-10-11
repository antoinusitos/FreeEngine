#pragma once

#include <SFML/Window.hpp>

class Window
{
public:
	Window();
	~Window();

	static Window& GetInstance();

	sf::Window* GetWindow();

	void Init();

	void Exit();

private :

	static Window _instance;

	sf::Window* _window;

};

