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
	void Update(float deltaTime);

	bool A_button_pressed = false;

	int  GetPort();
	XINPUT_GAMEPAD *GetState();
	bool CheckConnection();
	bool Refresh();

	bool IsPressed(WORD button);
	bool IsDown(WORD button);
	bool IsUp(WORD button);
	float GetLeftStickX();
	float GetLeftStickY();
	float GetRightStickX();
	float GetRightStickY();
	float GetLeftTrigger();
	float GetRightTrigger();

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
};

