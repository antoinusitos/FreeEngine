#include "Input.h"
#include <iostream>

Input* Input::_instance = NULL;

Input::Input()
{
	std::cout << "Creation Input" << std::endl;
	// Initialization of the map of the input
	_mapping = std::map<KEY, bool>();
	_mapping.emplace(KEY::SPACE, false);
	_mapping.emplace(KEY::ESCAPE, false);
}

Input::~Input()
{
	std::cout << "Destroy Input" << std::endl;
}

bool Input::MustClose()
{
	return _mustClose;
}

void Input::ProcessInput(sf::Window& window)
{
	// Process all events that happend in the SFML window
	while (window.pollEvent(_event))
	{
		switch (_event.type) 
		{
		case sf::Event::Closed:
			_mustClose = true;
			break;

		case sf::Event::KeyPressed:
			if (_event.key.code == sf::Keyboard::Space)
			{
				_mapping[KEY::SPACE] = true;
			}
			else if (_event.key.code == sf::Keyboard::Escape)
			{
				_mapping[KEY::ESCAPE] = true;
			}
			break;

		case sf::Event::KeyReleased:
			if (_event.key.code == sf::Keyboard::Space)
			{
				_mapping[KEY::SPACE] = false;
			}
			else if (_event.key.code == sf::Keyboard::Escape)
			{
				_mapping[KEY::ESCAPE] = false;
			}
			break;

		default:

			break;
		}
	}
}

bool Input::GetKeyPressed(KEY key)
{
	return _mapping.find(key)->second;
}