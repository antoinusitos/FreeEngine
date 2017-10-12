#pragma once
#define NULL 0

#include <vector>
#include "EngineObject.h"

class ObjectsManager
{
public:
	// Constructor
	ObjectsManager();
	// Destructor
	~ObjectsManager();

	// Get a unique instance of the time
	static ObjectsManager* GetInstance()
	{
		if (NULL == _instance)
		{
			_instance = new ObjectsManager;
		}

		return _instance;
	}

	void RegisterEngineObject(EngineObject* object);

	void UpdateAllEngineObjects(float deltaTime);
	void RenderAllEngineObjects();

private:
	// Unique instance of the time
	static ObjectsManager* _instance;

	std::vector<EngineObject*> _allEngineObjects;
};

