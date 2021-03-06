#include <iostream>
#include <iomanip>
#include <locale>
#include <sstream>
#include <string>

#include "ObjectsManager.h"
#include "GarbageCollector.h"
#include "Debug.h"
#include "EngineObject.h"

std::unique_ptr<ObjectsManager> ObjectsManager::_instance;
std::once_flag ObjectsManager::onceFlag;

ObjectsManager::ObjectsManager()
{
	//Debug::Instance().Print("Create Object manager");
}

ObjectsManager::~ObjectsManager()
{
	Debug::Instance().Print("remove object Manager", DebugMessageType::DEBUGLOG);

	for (std::vector<EngineObject*>::iterator it = _allEngineObjects.begin(); it != _allEngineObjects.end(); ++it)
	{
		delete (*it);
	}
	_allEngineObjects.clear();
}

void ObjectsManager::RegisterEngineObject(EngineObject* object)
{
	_allEngineObjects.push_back(object);
}

const int ObjectsManager::GetID()
{
	ID++;
	return ID-1;
}

void ObjectsManager::AwakeAllEngineObjects()
{
	for (std::vector<EngineObject*>::iterator it = _allEngineObjects.begin(); it != _allEngineObjects.end(); ++it)
	{
		(*it)->Awake();
	}
}

void ObjectsManager::StartAllEngineObjects()
{
	for (std::vector<EngineObject*>::iterator it = _allEngineObjects.begin(); it != _allEngineObjects.end(); ++it)
	{
		(*it)->Start();
	}
}

void ObjectsManager::UpdateAllEngineObjects(const float deltaTime)
{
	for (std::vector<EngineObject*>::iterator it = _allEngineObjects.begin(); it != _allEngineObjects.end(); ++it)
	{
		if((*it) != nullptr)
			(*it)->Update(deltaTime);
	}
}

void ObjectsManager::RenderAllEngineObjects(sf::RenderWindow* window)
{
	for (std::vector<EngineObject*>::iterator it = _allEngineObjects.begin(); it != _allEngineObjects.end(); ++it)
	{
		if ((*it) != nullptr)
			(*it)->Render(window);
	}
}

void ObjectsManager::DestroyObject(EngineObject* object)
{
	int index = -1;
	bool found = false;
	for (std::vector<EngineObject*>::iterator it = _allEngineObjects.begin(); it != _allEngineObjects.end(); ++it)
	{
		index++;
		if ((*it) == object)
		{
			found = true;
			break;
		}
	}
	
	if(found)
		_allEngineObjects.erase(_allEngineObjects.begin() + index);
}
