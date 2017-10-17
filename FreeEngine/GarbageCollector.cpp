#include <iostream>

#include "GarbageCollector.h"
#include "Debug.h"

GarbageCollector* GarbageCollector::_instance = NULL;

GarbageCollector::GarbageCollector()
{
	Debug::GetInstance()->Print("Create Garbage Collector");
}

GarbageCollector::~GarbageCollector()
{
}

void GarbageCollector::SetDestroyable(EngineObject* object)
{
	delete object;
	object = nullptr;
}