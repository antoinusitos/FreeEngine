#pragma once
#define NULL 0

#include <vector>
#include <memory>
#include <mutex>

#include "SFML\Graphics.hpp"

class EngineObject;

class ObjectsManager
{
public:
	// Constructor
	ObjectsManager();
	// Destructor
	~ObjectsManager();

	// Get a unique instance of the time
	static ObjectsManager& ObjectsManager::Instance()
	{
		std::call_once(ObjectsManager::onceFlag, []() {
			_instance.reset(new ObjectsManager);
			//std::cout << "Getting  ObjectsManager instance" << '\n';
		});

		return *(_instance.get());
	}

	void RegisterEngineObject(EngineObject* object);

	void AwakeAllEngineObjects();
	void StartAllEngineObjects();
	void UpdateAllEngineObjects(const float deltaTime);
	void RenderAllEngineObjects(sf::RenderWindow* window);
	void DestroyObject(EngineObject* object);

	const int GetID();

private:
	// Unique instance of the time
	static std::unique_ptr<ObjectsManager> _instance;
	static std::once_flag onceFlag;

	std::vector<EngineObject*> _allEngineObjects;

	int ID = 0;
};

