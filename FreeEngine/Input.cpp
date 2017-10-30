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
	_mapping = std::map<KEYCODE, InputKey>();
	InputKey ik = InputKey();
	ik.key = KEYCODE::SPACE;
	_mapping.emplace(KEYCODE::SPACE, ik);

	ik = InputKey();
	ik.key = KEYCODE::ESCAPE;
	_mapping.emplace(KEYCODE::ESCAPE, ik);

	ik = InputKey();
	ik.key = KEYCODE::ARROWUP;
	_mapping.emplace(KEYCODE::ARROWUP, ik);

	ik = InputKey();
	ik.key = KEYCODE::ARROWDOWN;
	_mapping.emplace(KEYCODE::ARROWDOWN, ik);

	ik = InputKey();
	ik.key = KEYCODE::ARROWRIGHT;
	_mapping.emplace(KEYCODE::ARROWRIGHT, ik);

	ik = InputKey();
	ik.key = KEYCODE::ARROWLEFT;
	_mapping.emplace(KEYCODE::ARROWLEFT, ik);

	ik = InputKey();
	ik.key = KEYCODE::F1;
	_mapping.emplace(KEYCODE::F1, ik);

	ik = InputKey();
	ik.key = KEYCODE::A;
	_mapping.emplace(KEYCODE::A, ik);

	ik = InputKey();
	ik.key = KEYCODE::B;
	_mapping.emplace(KEYCODE::B, ik);
}

bool Input::MustClose()
{
	return _mustClose;
}

void Input::ProcessInput(sf::Window& window)
{
	if (!_canInput) return;

	// Process all events that happend in the SFML window
	while (window.pollEvent(_event))
	{
		switch (_event.type)
		{
		case sf::Event::Closed:
			_mustClose = true;
			break;

		case sf::Event::KeyPressed:
		{
			KEYCODE k;
			bool keyExist = true;

			k = GetKeycodeAssociate(_event.key.code);

			if (k == KEYCODE::NONE)
				keyExist = false;

			if (keyExist)
			{
				_mapping[k].pressing = true;
				if (_mapping[k].init == false && _mapping[k].pressDown == false)
				{
					_mapping[k].init = true;
					_mapping[k].pressDown = true;
				}
			}

			break;
		}
		case sf::Event::KeyReleased:
		{
			KEYCODE k;
			bool keyExist = true;
			
			k = GetKeycodeAssociate(_event.key.code);

			if (k == KEYCODE::NONE)
				keyExist = false;

			if (keyExist)
			{
				_mapping[k].pressing = false;
				if (!_mapping[k].exit && !_mapping[k].release)
				{
					_mapping[k].exit = true;
					_mapping[k].release = true;
				}
			}

			break;
		}
		default:

			break;
		}
	}
}

bool Input::GetKeyDown(KEYCODE key)
{
	return _mapping.find(key)->second.pressDown;
}

bool Input::GetKeyReleased(KEYCODE key)
{
	return _mapping.find(key)->second.release;
}

bool Input::GetKeyPressed(KEYCODE key)
{
	return _mapping.find(key)->second.pressing;
}

void Input::SetCanInput(bool NewState)
{
	_canInput = NewState;
}

void Input::Update(float deltaTime)
{
	for (auto& x : _mapping)
	{
		if (x.second.init)
		{
			x.second.pressDown = false;
		}
		if (x.second.exit)
		{
			x.second.exit = false;
			x.second.release = false;
			x.second.init = false;
		}
	}
}

KEYCODE Input::GetKeycodeAssociate(sf::Keyboard::Key key)
{
	if (_event.key.code == sf::Keyboard::Space)
	{
		return KEYCODE::SPACE;
	}
	else if (_event.key.code == sf::Keyboard::Escape)
	{
		return KEYCODE::ESCAPE;
	}
	else if (_event.key.code == sf::Keyboard::F1)
	{
		return KEYCODE::F1;
	}
	else if (_event.key.code == sf::Keyboard::Up)
	{
		return KEYCODE::ARROWUP;
	}
	else if (_event.key.code == sf::Keyboard::Down)
	{
		return KEYCODE::ARROWDOWN;
	}
	else if (_event.key.code == sf::Keyboard::Right)
	{
		return KEYCODE::ARROWRIGHT;
	}
	else if (_event.key.code == sf::Keyboard::Left)
	{
		return KEYCODE::ARROWLEFT;
	}
	else if (_event.key.code == sf::Keyboard::A)
	{
		return KEYCODE::A;
	}
	else if (_event.key.code == sf::Keyboard::B)
	{
		return KEYCODE::B;
	}

	return KEYCODE::NONE;
}