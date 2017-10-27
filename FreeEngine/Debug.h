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
			//std::cout << "Getting  Debug instance" << '\n';
		});

		return *(_instance.get());
	}

	void Print(std::string message, DebugMessageType messageType);

	void SaveLog();

	void SetDebugWindow(DebugWindowLayout* newWindow);

private:
	// Unique instance of the time
	static std::unique_ptr<Debug> _instance;
	static std::once_flag onceFlag;

	std::vector<DebugMessage> _allString;

	DebugWindowLayout* debugWindow;
};

