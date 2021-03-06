#pragma once

#include <memory>
#include <mutex>

class EngineObject;

class GarbageCollector
{
public:
	// Constructor
	GarbageCollector();
	// Destructor
	~GarbageCollector();

	// Get a unique instance of the time
	static GarbageCollector& GarbageCollector::Instance()
	{
		std::call_once(GarbageCollector::onceFlag, []() {
			_instance.reset(new GarbageCollector);
		});

		return *(_instance.get());
	}

private:
	// Unique instance of the time
	static std::unique_ptr<GarbageCollector> _instance;
	static std::once_flag onceFlag;
};

