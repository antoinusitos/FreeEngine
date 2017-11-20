#include "Input.h"
#include <iostream>
#include "Debug.h"
#include "EditorManager.h"

std::unique_ptr<Input> Input::_instance;
std::once_flag Input::onceFlag;

Input::Input()
{
	//std::cout << "Creation Input" << std::endl;
	// Initialization of the map of the input
}

Input::~Input()
{
	Debug::Instance().Log("Destroy Input", DebugMessageType::DEBUGENGINE);
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
	ik.key = KEYCODE::ENTER;
	_mapping.emplace(KEYCODE::ENTER, ik);

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
	ik.key = KEYCODE::MOUSELEFT;
	_mapping.emplace(KEYCODE::MOUSELEFT, ik);

	ik = InputKey();
	ik.key = KEYCODE::MOUSERIGHT;
	_mapping.emplace(KEYCODE::MOUSERIGHT, ik);

	ik = InputKey();
	ik.key = KEYCODE::F1;
	_mapping.emplace(KEYCODE::F1, ik);

	ik = InputKey();
	ik.key = KEYCODE::A;
	_mapping.emplace(KEYCODE::A, ik);

	ik = InputKey();
	ik.key = KEYCODE::B;
	_mapping.emplace(KEYCODE::B, ik);

	ik = InputKey();
	ik.key = KEYCODE::C;
	_mapping.emplace(KEYCODE::C, ik);
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
			EditorManager::Instance().SetMustQuit();
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
		case sf::Event::MouseButtonPressed:
		{
			KEYCODE k;
			bool keyExist = true;

			k = GetMouseCodeAssociate(_event.mouseButton.button);

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
		case sf::Event::MouseButtonReleased:
		{
			KEYCODE k;
			bool keyExist = true;

			k = GetMouseCodeAssociate(_event.mouseButton.button);

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

const bool Input::GetKeyDown(const KEYCODE key)
{
	return _mapping.find(key)->second.pressDown;
}

const bool Input::GetKeyReleased(const KEYCODE key)
{
	return _mapping.find(key)->second.release;
}

const bool Input::GetKeyPressed(const KEYCODE key)
{
	return _mapping.find(key)->second.pressing;
}

void Input::SetCanInput(const bool NewState)
{
	_canInput = NewState;
}

void Input::Update(const float deltaTime)
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

const KEYCODE Input::GetMouseCodeAssociate(const sf::Mouse::Button button)
{
	if (button == sf::Mouse::Left)
	{
		return KEYCODE::MOUSELEFT;
	}
	else if (button == sf::Mouse::Right)
	{
		return KEYCODE::MOUSERIGHT;
	}

	return KEYCODE::NONE;
}

const KEYCODE Input::GetKeycodeAssociate(const sf::Keyboard::Key key)
{
	if (_event.key.code == sf::Keyboard::Space)
	{
		return KEYCODE::SPACE;
	}
	else if (_event.key.code == sf::Keyboard::Escape)
	{
		return KEYCODE::ESCAPE;
	}
	else if (_event.key.code == sf::Keyboard::Return)
	{
		return KEYCODE::ENTER;
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
	else if (_event.key.code == sf::Keyboard::C)
	{
		return KEYCODE::C;
	}

	return KEYCODE::NONE;
}

void Input::SaveMousePos(const sf::Window& window)
{
	sf::Vector2i localPosition = sf::Mouse::getPosition(window);
	_mousePosition = FVector2(localPosition.x, localPosition.y);
}

const FVector2 Input::GetMousePosition()
{
	return _mousePosition;
}