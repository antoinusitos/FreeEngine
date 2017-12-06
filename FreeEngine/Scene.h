#pragma once

#include "EngineObject.h"

class GameObject;

class Scene : public EngineObject
{
public:
	Scene(const std::string name);
	~Scene();

	virtual void PreAwake();
	virtual void Awake();
	virtual void Start();

	virtual void Update(const float deltaTime);
	virtual void Render(sf::RenderWindow* window);

	void Destroy();

	void SaveObject();
	void LoadObject();

	void AddDynamicObjectToScene(GameObject* newObject);
	void AddStaticObjectToScene(EngineObject* newObject);

	void RemoveDynamicObjectToScene(GameObject* object);
	void RemoveStaticObjectToScene(EngineObject* object);

	void SetTransition(bool newState);

	void ClearStaticObjects();
	void ClearDynamicObjects();

private:
	std::string _name;
	std::string _fileName;
	bool _loaded = false;
	bool _mustLoad = false;

	std::vector<EngineObject*> _staticObjectsInScene; // including objects to load (environment)
	std::vector<GameObject*> _dynamicObjectsInScene; // including objects spawned (player, particules, bullets, etc.)

protected:
	bool _transition = false;
};

