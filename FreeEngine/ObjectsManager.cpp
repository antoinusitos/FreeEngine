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
}

void ObjectsManager::RegisterEngineObject(EngineObject* object)
{

	_allEngineObjects.push_back(object);
}

int ObjectsManager::GetID()
{
	ID++;
	return ID-1;
}

void ObjectsManager::StartAllEngineObjects()
{
	for (std::vector<EngineObject*>::iterator it = _allEngineObjects.begin(); it != _allEngineObjects.end(); ++it)
	{
		(*it)->Start();
	}
}

void ObjectsManager::UpdateAllEngineObjects(float deltaTime)
{
	for (std::vector<EngineObject*>::iterator it = _allEngineObjects.begin(); it != _allEngineObjects.end(); ++it)
	{
		if((*it) != nullptr)
			(*it)->Update(deltaTime);
	}
}

void ObjectsManager::RenderAllEngineObjects()
{
	for (std::vector<EngineObject*>::iterator it = _allEngineObjects.begin(); it != _allEngineObjects.end(); ++it)
	{
		if ((*it) != nullptr)
			(*it)->Render();
	}
}

void ObjectsManager::DestroyObject(EngineObject* object)
{
	int index = -1;
	EngineObject* temp = nullptr;
	for (std::vector<EngineObject*>::iterator it = _allEngineObjects.begin(); it != _allEngineObjects.end(); ++it)
	{
		index++;
		if ((*it) == object)
		{
			temp = (*it);
			break;
		}
	}
	_allEngineObjects.erase(_allEngineObjects.begin() + index);
	//GarbageCollector::Instance().SetDestroyable(object);
}
