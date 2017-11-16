#pragma once

#include "EngineObject.h"

class Scene : public EngineObject
{
public:
	Scene(const std::string name);
	~Scene();

	void PreAwake();
	void Awake();
	void Start();

	void Update(const float deltaTime);
	void Render(sf::RenderWindow* window);

	void Destroy();

	void SaveObject();
	void LoadObject();

	void AddDynamicObjectToScene(EngineObject* newObject);
	void AddStaticObjectToScene(EngineObject* newObject);

private:
	std::string _name;
	std::string _fileName;
	bool _loaded = false;
	bool _mustLoad = false;

	std::vector<EngineObject*> _staticObjectsInScene; // including objects to load (environment)
	std::vector<EngineObject*> _dynamicObjectsInScene; // including objects spawned (player, particules, bullets, etc.)
};

