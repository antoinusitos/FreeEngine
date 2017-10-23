#include "Input.h"
#include <iostream>

std::unique_ptr<Input> Input::_instance;
std::once_flag Input::onceFlag;

Input::Input()
{
	//std::cout << "Creation Input" << std::endl;
	// Initialization of the map of the input
}

Input::~Input()
{
	std::cout << "Destroy Input" << std::endl;
}

void Input::Init()
{
	_mapping = std::map<KEY, bool>();
	_mapping.emplace(KEY::SPACE, false);
	_mapping.emplace(KEY::ESCAPE, false);
	_mapping.emplace(KEY::ARROWUP, false);
	_mapping.emplace(KEY::ARROWDOWN, false);
	_mapping.emplace(KEY::ARROWRIGHT, false);
	_mapping.emplace(KEY::ARROWLEFT, false);
	_mapping.emplace(KEY::A, false);
	_mapping.emplace(KEY::B, false);

	_lastMapping = std::map<KEY, bool>();
	_lastMapping.emplace(KEY::SPACE, false);
	_lastMapping.emplace(KEY::ESCAPE, false);
	_lastMapping.emplace(KEY::ARROWUP, false);
	_lastMapping.emplace(KEY::ARROWDOWN, false);
	_lastMapping.emplace(KEY::ARROWRIGHT, false);
	_lastMapping.emplace(KEY::ARROWLEFT, false);
	_lastMapping.emplace(KEY::A, false);
	_lastMapping.emplace(KEY::B, false);
}

bool Input::MustClose()
{
	return _mustClose;
}

void Input::ProcessInput(sf::Window& window)
{
	if (!_canInput) return;

	for (std::map<KEY, bool>::iterator it = _lastMapping.begin(); it != _lastMapping.end(); ++it)
		it->second = false;

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
			else if (_event.key.code == sf::Keyboard::Up)
			{
				_mapping[KEY::ARROWUP] = true;
			}
			else if (_event.key.code == sf::Keyboard::Down)
			{
				_mapping[KEY::ARROWDOWN] = true;
			}
			else if (_event.key.code == sf::Keyboard::Right)
			{
				_mapping[KEY::ARROWRIGHT] = true;
			}
			else if (_event.key.code == sf::Keyboard::Left)
			{
				_mapping[KEY::ARROWLEFT] = true;
			}
			else if (_event.key.code == sf::Keyboard::A)
			{
				_mapping[KEY::A] = true;
			}
			else if (_event.key.code == sf::Keyboard::B)
			{
				_mapping[KEY::B] = true;
			}
			break;

		case sf::Event::KeyReleased:
			if (_event.key.code == sf::Keyboard::Space)
			{
				_lastMapping[KEY::SPACE] = true;
				_mapping[KEY::SPACE] = false;
			}
			else if (_event.key.code == sf::Keyboard::Escape)
			{
				_lastMapping[KEY::ESCAPE] = true;
				_mapping[KEY::ESCAPE] = false;
			}
			else if (_event.key.code == sf::Keyboard::Up)
			{
				_lastMapping[KEY::ARROWUP] = true;
				_mapping[KEY::ARROWUP] = false;
			}
			else if (_event.key.code == sf::Keyboard::Down)
			{
				_lastMapping[KEY::ARROWDOWN] = true;
				_mapping[KEY::ARROWDOWN] = false;
			}
			else if (_event.key.code == sf::Keyboard::Right)
			{
				_lastMapping[KEY::ARROWRIGHT] = true;
				_mapping[KEY::ARROWRIGHT] = false;
			}
			else if (_event.key.code == sf::Keyboard::Left)
			{
				_lastMapping[KEY::ARROWLEFT] = true;
				_mapping[KEY::ARROWLEFT] = false;
			}
			else if (_event.key.code == sf::Keyboard::A)
			{
				_lastMapping[KEY::A] = true;
				_mapping[KEY::A] = false;
			}
			else if (_event.key.code == sf::Keyboard::B)
			{
				_lastMapping[KEY::B] = true;
				_mapping[KEY::B] = false;
			}
			break;

		default:

			break;
		}
	}
}

bool Input::GetKeyPressed(KEY key)
{
	return _mapping.find(key)->second != _lastMapping.find(key)->second;
}

void Input::SetCanInput(bool NewState)
{
	_canInput = NewState;
}