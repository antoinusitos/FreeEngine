#pragma once

#include <memory>
#include <mutex>

#include "Data.h"

class GameManager
{
public:
	GameManager();
	~GameManager();

	// Get a unique instance of the time
	static GameManager& GameManager::Instance()
	{
		std::call_once(GameManager::onceFlag, []() {
			_instance.reset(new GameManager);
			//std::cout << "Getting  Window instance" << '\n';
		});

		return *(_instance.get());
	}

	const bool GetMustQuit();
	void SetMustQuit();

	const GameState GetCurrentState();
	void ChangeCurrentState();

private:
	// Unique instance of the time
	static std::unique_ptr<GameManager> _instance;
	static std::once_flag onceFlag;

	GameState _currentState = GameState::PLAY;

	bool _mustQuit = false;
};

