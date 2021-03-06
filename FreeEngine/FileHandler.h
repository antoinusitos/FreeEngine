#pragma once

#include <string>
#include <vector>
#include <memory>
#include <mutex>
#include <iostream>
#include <fstream>

class FileObserver
{
public:
	virtual void NotifyChange() = 0;
};

struct Watcher
{
public:
	int ID;
	FileObserver* observer;
	std::string fileToObserve;
	time_t lastTime;
	
};

class FileHandler
{
public:
	FileHandler();
	~FileHandler();

	static FileHandler& FileHandler::Instance()
	{
		std::call_once(FileHandler::onceFlag, []()
		{
			_instance.reset(new FileHandler);
		});
		return *(_instance.get());
	}

	bool WriteFile(const std::string fileName, const std::string text);
	std::string ReadFile(const std::string fileName, bool* fileReadable);
	int RegisterNewWatcher(FileObserver* observer, const std::string fileName);
	void UpdateWatchers(const float deltaTime);
	void UnregisterWatcher(const int ID);

private:
	std::vector<Watcher> _allWatcher;
	static std::unique_ptr<FileHandler> _instance;
	static std::once_flag onceFlag;
	int ids;
};

