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
			std::cout << "Geting FileHandler Instance" << '\n';
		});
		return *(_instance.get());
	}

	bool WriteFile(std::string fileName, std::string text);
	std::string ReadFile(std::string fileName, bool* fileReadable);
	int RegisterNewWatcher(FileObserver* observer, std::string fileName);
	void UpdateWatchers(float deltaTime);
	void UnregisterWatcher(int ID);

private:
	std::vector<Watcher> _allWatcher;
	static std::unique_ptr<FileHandler> _instance;
	static std::once_flag onceFlag;
	int ids;
};

