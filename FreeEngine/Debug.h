#pragma once

#include <iostream>
#include <string>

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

private:
	// Unique instance of the time
	static Debug* _instance;
};

