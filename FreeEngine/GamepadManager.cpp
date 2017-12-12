#include "GamepadManager.h"
#include "Debug.h"

std::unique_ptr<GamepadManager> GamepadManager::_instance;
std::once_flag GamepadManager::onceFlag;

GamepadManager::GamepadManager()
{
	_deadzoneX = 0.05f;
	_deadzoneY = 0.02f;
}

GamepadManager::~GamepadManager()
{
}

void GamepadManager::Init()
{
	for (int i = 0; i < 4; i++)
	{
		_states.push_back(XINPUT_STATE());
		_gamepadValues.push_back(GamepadValues());

		ZeroMemory(&_states[i], sizeof(XINPUT_STATE));

		_buttonState.push_back(std::map<WORD, bool>());

		if (XInputGetState(i, &_states[i]) == ERROR_SUCCESS)
		{
			_buttonState[i].emplace(XINPUT_GAMEPAD_A, false);
			_buttonState[i].emplace(XINPUT_GAMEPAD_B, false);
			_buttonState[i].emplace(XINPUT_GAMEPAD_X, false);
			_buttonState[i].emplace(XINPUT_GAMEPAD_Y, false);

			_lastButtonState = _buttonState;

			// controller is connected on port i
			Debug::Instance().Print("Controller Connected to port " + i, DebugMessageType::DEBUGLOG);
		}
	}
}

void GamepadManager::Update(float deltaTime)
{
	if (!_wantToUseGamepad) return;

	if (!Refresh())
	{
		//TODO : rework
		if (_wasConnected && !_reminder)
		{
			//Debug::Instance().Print("Please connect an Xbox 360 controller.", DebugMessageType::DEBUGERROR);
			//_reminder = true;
		}
	}
	else
	{
		//TODO : rework
		/*if (!_wasConnected)
		{
			_reminder = false;
			_wasConnected = true;

			Debug::Instance().Print("Controller connected on port " + GetPort(), DebugMessageType::DEBUGWARNING);
		}*/
	}
}

const int GamepadManager::GetPort(int playerNumber)
{
	return _gamepadValues[playerNumber]._controllerId;
}

const XINPUT_GAMEPAD *GamepadManager::GetState(int playerNumber)
{
	return &_states[playerNumber].Gamepad;
}

bool GamepadManager::CheckConnection(int playerNumber)
{
	int controllerId = -1;

	int portTaken[4] = { -1, -1, -1, -1 };

	for (int players = 0; players < _nbPlayers; players++)
	{
		controllerId = -1;
		for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
		{
			XINPUT_STATE state;
			ZeroMemory(&state, sizeof(XINPUT_STATE));

			if (XInputGetState(i, &state) == ERROR_SUCCESS)
			{
				bool canTake = true;
				for (int p = 0; p < playerNumber; p++)
				{
					if (portTaken[p] == i)
						canTake = false;
				}
				if (canTake)
				{
					controllerId = i;
					portTaken[players] = i;
					_gamepadValues[playerNumber]._controllerId = controllerId;
					break;
				}
			}
		}

		if (controllerId == -1)
		{
			std::cout << "CANNOT AFFECT controller ID for player "<< players << " !" << '\n';
			return false;
		}

	}
	return true;
}

// Returns false if the controller has been disconnected
bool GamepadManager::Refresh()
{
	for (int i = 0; i < _nbPlayers; i++)
	{
		CheckConnection(i);
	}

	for (int i = 0; i < _nbPlayers; i++)
	{
		if (_gamepadValues[i]._controllerId != -1)
		{
			ZeroMemory(&_states[i], sizeof(XINPUT_STATE));
			if (XInputGetState(_gamepadValues[i]._controllerId, &_states[i]) != ERROR_SUCCESS)
			{
				_gamepadValues[i]._controllerId = -1;
				return false;
			}

			_lastButtonState = _buttonState;

			_buttonState[i][XINPUT_GAMEPAD_A] = (_states[i].Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0;
			_buttonState[i][XINPUT_GAMEPAD_B] = (_states[i].Gamepad.wButtons & XINPUT_GAMEPAD_B) != 0;
			_buttonState[i][XINPUT_GAMEPAD_X] = (_states[i].Gamepad.wButtons & XINPUT_GAMEPAD_X) != 0;
			_buttonState[i][XINPUT_GAMEPAD_Y] = (_states[i].Gamepad.wButtons & XINPUT_GAMEPAD_Y) != 0;

			float normLX = fmaxf(-1, static_cast<float>(_states[i].Gamepad.sThumbLX) / 32767);
			float normLY = fmaxf(-1, static_cast<float>(_states[i].Gamepad.sThumbLY) / 32767);

			_gamepadValues[i]._leftStickX = (abs(normLX) < _deadzoneX ? 0 : (abs(normLX) - _deadzoneX) * (normLX / abs(normLX)));
			_gamepadValues[i]._leftStickY = (abs(normLY) < _deadzoneY ? 0 : (abs(normLY) - _deadzoneY) * (normLY / abs(normLY)));

			if (_deadzoneX > 0) _gamepadValues[i]._leftStickX *= 1 / (1 - _deadzoneX);
			if (_deadzoneY > 0) _gamepadValues[i]._leftStickY *= 1 / (1 - _deadzoneY);

			float normRX = fmaxf(-1, static_cast<float>(_states[i].Gamepad.sThumbRX) / 32767);
			float normRY = fmaxf(-1, static_cast<float>(_states[i].Gamepad.sThumbRY) / 32767);

			_gamepadValues[i]._rightStickX = (abs(normRX) < _deadzoneX ? 0 : (abs(normRX) - _deadzoneX) * (normRX / abs(normRX)));
			_gamepadValues[i]._rightStickY = (abs(normRY) < _deadzoneY ? 0 : (abs(normRY) - _deadzoneY) * (normRY / abs(normRY)));

			if (_deadzoneX > 0) _gamepadValues[i]._rightStickX *= 1 / (1 - _deadzoneX);
			if (_deadzoneY > 0) _gamepadValues[i]._rightStickY *= 1 / (1 - _deadzoneY);

			_gamepadValues[i]._leftTrigger = static_cast<float>(_states[i].Gamepad.bLeftTrigger) / 255;
			_gamepadValues[i]._rightTrigger = static_cast<float>(_states[i].Gamepad.bRightTrigger) / 255;
		}
	}
	return true;
}

const bool GamepadManager::IsPressed(const WORD button, int playerNumber)
{
	return (_states[playerNumber].Gamepad.wButtons & button) != 0;
}

const bool GamepadManager::IsDown(const WORD button, int playerNumber)
{
	return (_buttonState[playerNumber][button] && !_lastButtonState[playerNumber][button]);
}

const bool GamepadManager::IsUp(const WORD button, int playerNumber)
{
	return (!_buttonState[playerNumber][button] && _lastButtonState[playerNumber][button]);
}

const float GamepadManager::GetLeftStickX(int playerNumber) { return _gamepadValues[playerNumber]._leftStickX; }
const float GamepadManager::GetLeftStickY(int playerNumber) { return _gamepadValues[playerNumber]._leftStickY; }
const float GamepadManager::GetRightStickX(int playerNumber) { return _gamepadValues[playerNumber]._rightStickX; }
const float GamepadManager::GetRightStickY(int playerNumber) { return _gamepadValues[playerNumber]._rightStickY; }
const float GamepadManager::GetLeftTrigger(int playerNumber) { return _gamepadValues[playerNumber]._leftTrigger; }
const float GamepadManager::GetRightTrigger(int playerNumber) { return _gamepadValues[playerNumber]._rightTrigger; }

void GamepadManager::SetWantToUseGamepad(bool newState, int nbPlayers)
{
	_wantToUseGamepad = newState;
	_nbPlayers = nbPlayers;
}