#pragma once

#include <memory>
#include <mutex>

#include "Data.h"

class EditorManager
{
public:
	EditorManager();
	~EditorManager();

	// Get a unique instance of the time
	static EditorManager& EditorManager::Instance()
	{
		std::call_once(EditorManager::onceFlag, []() {
			_instance.reset(new EditorManager);
		});

		return *(_instance.get());
	}

	const bool GetMustQuit();
	void SetMustQuit();

	const EditorState GetCurrentState();
	void ChangeCurrentState();

private:
	// Unique instance of the time
	static std::unique_ptr<EditorManager> _instance;
	static std::once_flag onceFlag;

	EditorState _currentState = EditorState::RUNNING;

	bool _mustQuit = false;
};

