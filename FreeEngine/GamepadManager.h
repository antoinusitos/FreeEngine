#pragma once

#include <windows.h>
#include <Xinput.h>
#include <memory>
#include <mutex>
#include <map>
#include <vector>
#include "Data.h"

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
		});

		return *(_instance.get());
	}

	void Init();
	void Update(const float deltaTime);

	bool A_button_pressed = false;

	const int GetPort(int playerNumber);
	const XINPUT_GAMEPAD *GetState(int playerNumber);
	bool CheckConnection(int playerNumber);
	bool Refresh();

	const bool IsPressed(const WORD button, int playerNumber);
	const bool IsDown(const WORD button, int playerNumber);
	const bool IsUp(const WORD button, int playerNumber);
	const float GetLeftStickX(int playerNumber);
	const float GetLeftStickY(int playerNumber);
	const float GetRightStickX(int playerNumber);
	const float GetRightStickY(int playerNumber);
	const float GetLeftTrigger(int playerNumber);
	const float GetRightTrigger(int playerNumber);

	void SetWantToUseGamepad(bool newState, int nbPlayers);

private:
	// Unique instance of the time
	static std::unique_ptr<GamepadManager> _instance;
	static std::once_flag onceFlag;

	std::vector<XINPUT_STATE> _states;

	int _nbPlayers = 0;

	std::vector<std::map<WORD, bool>> _buttonState;
	std::vector<std::map<WORD, bool>> _lastButtonState;

	float _deadzoneX;
	float _deadzoneY;

	std::vector<GamepadValues> _gamepadValues;
	
	bool _wasConnected = true;
	bool _reminder = false;
	bool _wantToUseGamepad = false;
};

