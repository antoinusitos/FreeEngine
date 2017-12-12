#pragma once

#include <memory>
#include <mutex>
#include <iostream>
#include <string>
#include <vector>

#include "DebugWindowLayout.h"
#include "Data.h"

class Debug
{
public:
	// Constructor
	Debug();
	// Destructor
	~Debug();

	// Get a unique instance of the time
	static Debug& Debug::Instance()
	{
		std::call_once(Debug::onceFlag, []() {
			_instance.reset(new Debug);
		});

		return *(_instance.get());
	}

	//Print a message in the console and windows prompt
	void Print(const std::string message, const DebugMessageType messageType);
	//Log a message only in the windows prompt
	void Log(const std::string message, const DebugMessageType messageType);

	const void SaveLog();

	void SetDebugWindow(DebugWindowLayout* newWindow);

private:
	// Unique instance of the time
	static std::unique_ptr<Debug> _instance;
	static std::once_flag onceFlag;

	std::vector<DebugMessage> _allString;

	DebugWindowLayout* debugWindow;
};

