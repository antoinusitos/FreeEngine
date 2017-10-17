#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "DebugWindowLayout.h"

class Debug
{
public:
	// Constructor
	Debug();
	// Destructor
	~Debug();

	// Get a unique instance of the time
	static Debug* GetInstance()
	{
		if (NULL == _instance)
		{
			_instance = new Debug;
		}

		return _instance;
	}

	void Print(std::string message);

	void SaveLog();

	void SetDebugWindow(DebugWindowLayout* newWindow);

private:
	// Unique instance of the time
	static Debug* _instance;

	std::vector<std::string> _allString;

	DebugWindowLayout* debugWindow = nullptr;
};

