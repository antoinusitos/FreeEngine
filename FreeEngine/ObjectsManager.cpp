#include <iostream>
#include "ObjectsManager.h"
#include <iomanip>
#include <locale>
#include <sstream>
#include <string>

ObjectsManager* ObjectsManager::_instance = NULL;

ObjectsManager::ObjectsManager()
{
	std::cout << " Create Object manager" << std::endl;
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
	for (std::vector<EngineObject*>::iterator it = _allEngineObjects.begin(); it != _allEngineObjects.end(); ++it)
	{
		index++;
		if ((*it) == object)
			break;
	}
	_allEngineObjects.erase(_allEngineObjects.begin() + index);
}
