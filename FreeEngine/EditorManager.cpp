#include "EditorManager.h"

std::unique_ptr<EditorManager> EditorManager::_instance;
std::once_flag EditorManager::onceFlag;

EditorManager::EditorManager()
{
	_currentState = EditorState::EDITING;
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