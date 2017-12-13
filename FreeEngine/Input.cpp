#include "Input.h"
#include <iostream>
#include "Debug.h"
#include "EditorManager.h"

std::unique_ptr<Input> Input::_instance;
std::once_flag Input::onceFlag;

Input::Input()
{
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
	ik.key = KEYCODE::RETURN;
	_mapping.emplace(KEYCODE::RETURN, ik);

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
	ik.key = KEYCODE::F2;
	_mapping.emplace(KEYCODE::F2, ik);

	ik = InputKey();
	ik.key = KEYCODE::A;
	_mapping.emplace(KEYCODE::A, ik);

	ik = InputKey();
	ik.key = KEYCODE::B;
	_mapping.emplace(KEYCODE::B, ik);

	ik = InputKey();
	ik.key = KEYCODE::C;
	_mapping.emplace(KEYCODE::C, ik);

	ik = InputKey();
	ik.key = KEYCODE::D;
	_mapping.emplace(KEYCODE::D, ik);

	ik = InputKey();
	ik.key = KEYCODE::E;
	_mapping.emplace(KEYCODE::E, ik);

	ik = InputKey();
	ik.key = KEYCODE::F;
	_mapping.emplace(KEYCODE::F, ik);

	ik = InputKey();
	ik.key = KEYCODE::G;
	_mapping.emplace(KEYCODE::G, ik);

	ik = InputKey();
	ik.key = KEYCODE::H;
	_mapping.emplace(KEYCODE::H, ik);

	ik = InputKey();
	ik.key = KEYCODE::I;
	_mapping.emplace(KEYCODE::I, ik);

	ik = InputKey();
	ik.key = KEYCODE::J;
	_mapping.emplace(KEYCODE::J, ik);

	ik = InputKey();
	ik.key = KEYCODE::K;
	_mapping.emplace(KEYCODE::K, ik);

	ik = InputKey();
	ik.key = KEYCODE::L;
	_mapping.emplace(KEYCODE::L, ik);

	ik = InputKey();
	ik.key = KEYCODE::M;
	_mapping.emplace(KEYCODE::M, ik);

	ik = InputKey();
	ik.key = KEYCODE::N;
	_mapping.emplace(KEYCODE::N, ik);

	ik = InputKey();
	ik.key = KEYCODE::O;
	_mapping.emplace(KEYCODE::O, ik);

	ik = InputKey();
	ik.key = KEYCODE::P;
	_mapping.emplace(KEYCODE::P, ik);

	ik = InputKey();
	ik.key = KEYCODE::Q;
	_mapping.emplace(KEYCODE::Q, ik);

	ik = InputKey();
	ik.key = KEYCODE::R;
	_mapping.emplace(KEYCODE::R, ik);

	ik = InputKey();
	ik.key = KEYCODE::S;
	_mapping.emplace(KEYCODE::S, ik);

	ik = InputKey();
	ik.key = KEYCODE::T;
	_mapping.emplace(KEYCODE::T, ik);

	ik = InputKey();
	ik.key = KEYCODE::U;
	_mapping.emplace(KEYCODE::U, ik);

	ik = InputKey();
	ik.key = KEYCODE::V;
	_mapping.emplace(KEYCODE::V, ik);

	ik = InputKey();
	ik.key = KEYCODE::W;
	_mapping.emplace(KEYCODE::W, ik);

	ik = InputKey();
	ik.key = KEYCODE::X;
	_mapping.emplace(KEYCODE::X, ik);

	ik = InputKey();
	ik.key = KEYCODE::Y;
	_mapping.emplace(KEYCODE::Y, ik);

	ik = InputKey();
	ik.key = KEYCODE::Z;
	_mapping.emplace(KEYCODE::Z, ik);

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

			ConvertKeyToChar(_event.key.code);

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
	else if (_event.key.code == sf::Keyboard::BackSpace)
	{
		return KEYCODE::RETURN;
	}
	else if (_event.key.code == sf::Keyboard::F1)
	{
		return KEYCODE::F1;
	}
	else if (_event.key.code == sf::Keyboard::F2)
	{
		return KEYCODE::F2;
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
	else if (_event.key.code == sf::Keyboard::D)
	{
		return KEYCODE::D;
	}
	else if (_event.key.code == sf::Keyboard::E)
	{
		return KEYCODE::E;
	}
	else if (_event.key.code == sf::Keyboard::F)
	{
		return KEYCODE::F;
	}
	else if (_event.key.code == sf::Keyboard::G)
	{
		return KEYCODE::G;
	}
	else if (_event.key.code == sf::Keyboard::H)
	{
		return KEYCODE::H;
	}
	else if (_event.key.code == sf::Keyboard::I)
	{
		return KEYCODE::I;
	}
	else if (_event.key.code == sf::Keyboard::J)
	{
		return KEYCODE::J;
	}
	else if (_event.key.code == sf::Keyboard::K)
	{
		return KEYCODE::K;
	}
	else if (_event.key.code == sf::Keyboard::L)
	{
		return KEYCODE::L;
	}
	else if (_event.key.code == sf::Keyboard::M)
	{
		return KEYCODE::M;
	}
	else if (_event.key.code == sf::Keyboard::N)
	{
		return KEYCODE::N;
	}
	else if (_event.key.code == sf::Keyboard::O)
	{
		return KEYCODE::O;
	}
	else if (_event.key.code == sf::Keyboard::P)
	{
		return KEYCODE::P;
	}
	else if (_event.key.code == sf::Keyboard::Q)
	{
		return KEYCODE::Q;
	}
	else if (_event.key.code == sf::Keyboard::R)
	{
		return KEYCODE::R;
	}
	else if (_event.key.code == sf::Keyboard::S)
	{
		return KEYCODE::S;
	}
	else if (_event.key.code == sf::Keyboard::T)
	{
		return KEYCODE::T;
	}
	else if (_event.key.code == sf::Keyboard::U)
	{
		return KEYCODE::U;
	}
	else if (_event.key.code == sf::Keyboard::V)
	{
		return KEYCODE::V;
	}
	else if (_event.key.code == sf::Keyboard::W)
	{
		return KEYCODE::W;
	}
	else if (_event.key.code == sf::Keyboard::X)
	{
		return KEYCODE::X;
	}
	else if (_event.key.code == sf::Keyboard::Y)
	{
		return KEYCODE::Y;
	}
	else if (_event.key.code == sf::Keyboard::Z)
	{
		return KEYCODE::Z;
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

std::string Input::GetLastInput()
{
	std::string s = _lastInput;
	_lastInput = "";
	return s;
}

void Input::RemoveLastInput()
{
	_lastInput = "";
}

bool Input::MustEraseOnLetter()
{
	bool temp = _mustErase;
	_mustErase = false;
	return temp;
}

void Input::ConvertKeyToChar(const sf::Keyboard::Key key)
{
	if (_event.key.code == sf::Keyboard::A)
	{
		_lastInput = 'A';
	}
	else if (_event.key.code == sf::Keyboard::B)
	{
		_lastInput = 'B';
	}
	else if (_event.key.code == sf::Keyboard::C)
	{
		_lastInput = 'C';
	}
	else if (_event.key.code == sf::Keyboard::D)
	{
		_lastInput = 'D';
	}
	else if (_event.key.code == sf::Keyboard::E)
	{
		_lastInput = 'E';
	}
	else if (_event.key.code == sf::Keyboard::F)
	{
		_lastInput = 'F';
	}
	else if (_event.key.code == sf::Keyboard::G)
	{
		_lastInput = 'G';
	}
	else if (_event.key.code == sf::Keyboard::H)
	{
		_lastInput = 'H';
	}
	else if (_event.key.code == sf::Keyboard::I)
	{
		_lastInput = 'I';
	}
	else if (_event.key.code == sf::Keyboard::J)
	{
		_lastInput = 'J';
	}
	else if (_event.key.code == sf::Keyboard::K)
	{
		_lastInput = 'K';
	}
	else if (_event.key.code == sf::Keyboard::L)
	{
		_lastInput = 'L';
	}
	else if (_event.key.code == sf::Keyboard::M)
	{
		_lastInput = 'M';
	}
	else if (_event.key.code == sf::Keyboard::N)
	{
		_lastInput = 'N';
	}
	else if (_event.key.code == sf::Keyboard::O)
	{
		_lastInput = 'O';
	}
	else if (_event.key.code == sf::Keyboard::P)
	{
		_lastInput = 'P';
	}
	else if (_event.key.code == sf::Keyboard::Q)
	{
		_lastInput = 'Q';
	}
	else if (_event.key.code == sf::Keyboard::R)
	{
		_lastInput = 'R';
	}
	else if (_event.key.code == sf::Keyboard::S)
	{
		_lastInput = 'S';
	}
	else if (_event.key.code == sf::Keyboard::T)
	{
		_lastInput = 'T';
	}
	else if (_event.key.code == sf::Keyboard::U)
	{
		_lastInput = 'U';
	}
	else if (_event.key.code == sf::Keyboard::V)
	{
		_lastInput = 'V';
	}
	else if (_event.key.code == sf::Keyboard::W)
	{
		_lastInput = 'W';
	}
	else if (_event.key.code == sf::Keyboard::X)
	{
		_lastInput = 'X';
	}
	else if (_event.key.code == sf::Keyboard::Y)
	{
		_lastInput = 'Y';
	}
	else if (_event.key.code == sf::Keyboard::Z)
	{
		_lastInput = 'Z';
	}
	else if (_event.key.code == sf::Keyboard::Space)
	{
		_lastInput = ' ';
	}
	else if (_event.key.code == sf::Keyboard::BackSpace)
	{
		_mustErase = true;
		_lastInput = "";
	}
}