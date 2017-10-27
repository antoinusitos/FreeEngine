#include <iostream>

#include "GarbageCollector.h"
#include "EngineObject.h"
#include "Debug.h"

std::unique_ptr<GarbageCollector> GarbageCollector::_instance;
std::once_flag GarbageCollector::onceFlag;

GarbageCollector::GarbageCollector()
{
	//Debug::Instance().Print("Create Garbage Collector");
}

GarbageCollector::~GarbageCollector()
{
}