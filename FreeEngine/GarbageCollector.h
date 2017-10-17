#pragma once

#include "EngineObject.h"

class GarbageCollector
{
public:
	// Constructor
	GarbageCollector();
	// Destructor
	~GarbageCollector();

	// Get a unique instance of the time
	static GarbageCollector* GetInstance()
	{
		if (NULL == _instance)
		{
			_instance = new GarbageCollector;
		}

		return _instance;
	}

	void SetDestroyable(EngineObject* object);

private:
	// Unique instance of the time
	static GarbageCollector* _instance;
};

