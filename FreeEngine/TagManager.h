#pragma once

#include <string>
#include <iostream>
#include <map>
#include <memory>
#include <mutex>

class TagManager
{
public:
	TagManager();
	~TagManager();

	// Get a unique instance of the time
	static TagManager& TagManager::Instance()
	{
		std::call_once(TagManager::onceFlag, []() {
			_instance.reset(new TagManager);
			//std::cout << "Getting  Window instance" << '\n';
		});

		return *(_instance.get());
	}

	void AddTag(std::string newTag);
	void RemoveTag(std::string newTag);
	int GetTagID(std::string tag);

private:
	// Unique instance of the time
	static std::unique_ptr<TagManager> _instance;
	static std::once_flag onceFlag;

	std::map<int, std::string> _tags;
};

