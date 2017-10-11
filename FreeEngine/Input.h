#pragma once

#include <SFML/Window.hpp>

#include <map> 

enum KEY
{
SPACE,
ESCAPE,
};

class Input
{
public:
	Input();
	~Input();
	static Input& GetInstance();

	void ProcessInput(sf::Window& window);

	bool GetKeyPressed(KEY key);

private :

	sf::Event _event;

	static Input _instance;

	std::map<KEY, bool> _mapping;
};


