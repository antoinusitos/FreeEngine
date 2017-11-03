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
