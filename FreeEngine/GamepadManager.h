#pragma once

#include <windows.h>
#include <Xinput.h>
#include <memory>
#include <mutex>
#include <map>

class GamepadManager
{
public:
	GamepadManager();
	~GamepadManager();

	// Get a unique instance of the time
	static GamepadManager& GamepadManager::Instance()
	{
		std::call_once(GamepadManager::onceFlag, []() {
			_instance.reset(new GamepadManager);
			//std::cout << "Getting  Window instance" << '\n';
		});

		return *(_instance.get());
	}

	void Init();
	void Update(const float deltaTime);

	bool A_button_pressed = false;

	const int GetPort();
	const XINPUT_GAMEPAD *GetState();
	bool CheckConnection();
	bool Refresh();

	const bool IsPressed(const WORD button);
	const bool IsDown(const WORD button);
	const bool IsUp(const WORD button);
	const float GetLeftStickX();
	const float GetLeftStickY();
	const float GetRightStickX();
	const float GetRightStickY();
	const float GetLeftTrigger();
	const float GetRightTrigger();

	void SetWantToUseGamepad(bool newState);

private:
	// Unique instance of the time
	static std::unique_ptr<GamepadManager> _instance;
	static std::once_flag onceFlag;

	XINPUT_STATE _state;
	int _controllerId = -1;

	std::map<WORD, bool> _buttonState;
	std::map<WORD, bool> _lastButtonState;

	float _deadzoneX;
	float _deadzoneY;

	float _leftStickX;
	float _leftStickY;
	float _rightStickX;
	float _rightStickY;
	float _leftTrigger;
	float _rightTrigger;

	bool _wasConnected = true;
	bool _reminder = false;
	bool _wantToUseGamepad = false;
};

