#include <iostream>
#include "ObjectsManager.h"

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

void ObjectsManager::UpdateAllEngineObjects(float deltaTime)
{
	for (std::vector<EngineObject*>::iterator it = _allEngineObjects.begin(); it != _allEngineObjects.end(); ++it)
	{
		(*it)->Update(deltaTime);
	}
}

void ObjectsManager::RenderAllEngineObjects()
{
	for (std::vector<EngineObject*>::iterator it = _allEngineObjects.begin(); it != _allEngineObjects.end(); ++it)
	{
		(*it)->Render();
	}
}