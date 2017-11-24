#include "GameManager.h"

std::unique_ptr<GameManager> GameManager::_instance;
std::once_flag GameManager::onceFlag;

GameManager::GameManager()
{
	_currentState = GameState::PLAY;
}

GameManager::~GameManager()
{
}

const bool GameManager::GetMustQuit()
{
	return _mustQuit;
}

void GameManager::SetMustQuit()
{
	_mustQuit = true;
}

const GameState GameManager::GetCurrentState()
{
	return _currentState;
}

void GameManager::ChangeCurrentState()
{
	if (_currentState == GameState::PAUSE)
		_currentState = GameState::PLAY;
	else
		_currentState = GameState::PAUSE;
}