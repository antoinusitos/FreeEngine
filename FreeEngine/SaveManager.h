#pragma once

#include <vector>
#include <string>
#include <memory>
#include <mutex>

#include "Data.h"

class SaveManager
{
public:
	SaveManager();
	~SaveManager();

	// Get a unique instance of the time
	static SaveManager& SaveManager::Instance()
	{
		std::call_once(SaveManager::onceFlag, []() {
			_instance.reset(new SaveManager);
		});

		return *(_instance.get());
	}

	void SetFloat(const std::string name, const float value);
	void SetInt(const std::string name, const int value);
	void SetString(const std::string name, const std::string value);
	void SetTransform(const std::string name, Transform* value);

	const float GetFloat(const std::string name, bool* hasRecover);
	const int GetInt(const std::string name, bool* hasRecover);
	const std::string GetString(const std::string name, bool* hasRecover);
	const Transform GetTransform(const std::string name, bool* hasRecover);

	void SaveAll();
	void LoadAll();

private:
	std::vector<SaveInfo*> _allInfos;

	// Unique instance of the time
	static std::unique_ptr<SaveManager> _instance;
	static std::once_flag onceFlag;
};

