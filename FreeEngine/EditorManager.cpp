#include "EditorManager.h"

std::unique_ptr<EditorManager> EditorManager::_instance;
std::once_flag EditorManager::onceFlag;

EditorManager::EditorManager()
{
	_currentState = EditorState::RUNNING;
}

EditorManager::~EditorManager()
{
}

const bool EditorManager::GetMustQuit()
{
	return _mustQuit;
}

void EditorManager::SetMustQuit()
{
	_mustQuit = true;
}

const EditorState EditorManager::GetCurrentState()
{
	return _currentState;
}

void EditorManager::ChangeCurrentState()
{
	if(_currentState == EditorState::EDITING)
		_currentState = EditorState::RUNNING;
	else
		_currentState = EditorState::EDITING;
}