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
	ZeroMemory(&_state, sizeof(XINPUT_STATE));

	if (XInputGetState(0, &_state) == ERROR_SUCCESS)
	{
		_buttonState.emplace(XINPUT_GAMEPAD_A, false);
		_buttonState.emplace(XINPUT_GAMEPAD_B, false);
		_buttonState.emplace(XINPUT_GAMEPAD_X, false);
		_buttonState.emplace(XINPUT_GAMEPAD_Y, false);

		_lastButtonState = _buttonState;

		// controller is connected on port 0
		Debug::Instance().Print("Controller Connected to port 0", DebugMessageType::DEBUGLOG);
	}
}

void GamepadManager::Update(float deltaTime)
{
	if (!Refresh())
	{
		if (_wasConnected)
		{
			Debug::Instance().Print("Please connect an Xbox 360 controller.", DebugMessageType::DEBUGERROR);
		}
	}
	else
	{
		if (!_wasConnected)
		{
			_wasConnected = true;

			Debug::Instance().Print("Controller connected on port " + GetPort(), DebugMessageType::DEBUGWARNING);
		}
	}
}

int GamepadManager::GetPort()
{
	return _controllerId + 1;
}

XINPUT_GAMEPAD *GamepadManager::GetState()
{
	return &_state.Gamepad;
}

bool GamepadManager::CheckConnection()
{
	int controllerId = -1;

	for (DWORD i = 0; i < XUSER_MAX_COUNT && controllerId == -1; i++)
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		if (XInputGetState(i, &state) == ERROR_SUCCESS)
			controllerId = i;
	}

	_controllerId = controllerId;

	return controllerId != -1;
}

// Returns false if the controller has been disconnected
bool GamepadManager::Refresh()
{
	if (_controllerId == -1)
		CheckConnection();

	if (_controllerId != -1)
	{
		ZeroMemory(&_state, sizeof(XINPUT_STATE));
		if (XInputGetState(_controllerId, &_state) != ERROR_SUCCESS)
		{
			_controllerId = -1;
			return false;
		}

		_lastButtonState = _buttonState;

		_buttonState[XINPUT_GAMEPAD_A] = (_state.Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0;
		_buttonState[XINPUT_GAMEPAD_B] = (_state.Gamepad.wButtons & XINPUT_GAMEPAD_B) != 0;
		_buttonState[XINPUT_GAMEPAD_X] = (_state.Gamepad.wButtons & XINPUT_GAMEPAD_X) != 0;
		_buttonState[XINPUT_GAMEPAD_Y] = (_state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) != 0;

		float normLX = fmaxf(-1, (float)_state.Gamepad.sThumbLX / 32767);
		float normLY = fmaxf(-1, (float)_state.Gamepad.sThumbLY / 32767);

		_leftStickX = (abs(normLX) < _deadzoneX ? 0 : (abs(normLX) - _deadzoneX) * (normLX / abs(normLX)));
		_leftStickY = (abs(normLY) < _deadzoneY ? 0 : (abs(normLY) - _deadzoneY) * (normLY / abs(normLY)));

		if (_deadzoneX > 0) _leftStickX *= 1 / (1 - _deadzoneX);
		if (_deadzoneY > 0) _leftStickY *= 1 / (1 - _deadzoneY);

		float normRX = fmaxf(-1, (float)_state.Gamepad.sThumbRX / 32767);
		float normRY = fmaxf(-1, (float)_state.Gamepad.sThumbRY / 32767);

		_rightStickX = (abs(normRX) < _deadzoneX ? 0 : (abs(normRX) - _deadzoneX) * (normRX / abs(normRX)));
		_rightStickY = (abs(normRY) < _deadzoneY ? 0 : (abs(normRY) - _deadzoneY) * (normRY / abs(normRY)));

		if (_deadzoneX > 0) _rightStickX *= 1 / (1 - _deadzoneX);
		if (_deadzoneY > 0) _rightStickY *= 1 / (1 - _deadzoneY);

		_leftTrigger = (float)_state.Gamepad.bLeftTrigger / 255;
		_rightTrigger = (float)_state.Gamepad.bRightTrigger / 255;

		return true;
	}
	return false;
}

bool GamepadManager::IsPressed(WORD button)
{
	return (_state.Gamepad.wButtons & button) != 0;
}

bool GamepadManager::IsDown(WORD button)
{
	return (_buttonState[button] && !_lastButtonState[button]);
}

bool GamepadManager::IsUp(WORD button)
{
	return (!_buttonState[button] && _lastButtonState[button]);
}

float GamepadManager::GetLeftStickX() { return _leftStickX; }
float GamepadManager::GetLeftStickY() { return _leftStickY; }
float GamepadManager::GetRightStickX() { return _rightStickX; }
float GamepadManager::GetRightStickY() { return _rightStickY; }
float GamepadManager::GetLeftTrigger() { return _leftTrigger; }
float GamepadManager::GetRightTrigger() { return _rightTrigger; }