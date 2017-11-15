#include "Scene.h"

Scene::Scene(const std::string name)
{
	_name = name;
}

Scene::~Scene()
{
}

void Scene::PreAwake()
{
	// only for the scene
}

void Scene::Awake()
{
	// awake the scene
	// awake all objects in the scene
	for (std::vector<EngineObject*>::iterator it = _staticObjectsInScene.begin(); it != _staticObjectsInScene.end(); it++)
	{
		(*it)->Awake();
	}
	for (std::vector<EngineObject*>::iterator it = _dynamicObjectsInScene.begin(); it != _dynamicObjectsInScene.end(); it++)
	{
		(*it)->Awake();
	}
}

void Scene::Start()
{
	// start the scene
	// start all objects in the scene

	for (std::vector<EngineObject*>::iterator it = _staticObjectsInScene.begin(); it != _staticObjectsInScene.end(); it++)
	{
		(*it)->Start();
	}
	for (std::vector<EngineObject*>::iterator it = _dynamicObjectsInScene.begin(); it != _dynamicObjectsInScene.end(); it++)
	{
		(*it)->Start();
	}
}

void Scene::Update(const float deltaTime)
{
	// update all objects in the scene
	for (std::vector<EngineObject*>::iterator it = _staticObjectsInScene.begin(); it != _staticObjectsInScene.end(); it++)
	{
		(*it)->Update(deltaTime);
	}
	for (std::vector<EngineObject*>::iterator it = _dynamicObjectsInScene.begin(); it != _dynamicObjectsInScene.end(); it++)
	{
		(*it)->Update(deltaTime);
	}
}

void Scene::Render(sf::RenderWindow* window)
{
	// render all objects in the scene
	for (std::vector<EngineObject*>::iterator it = _staticObjectsInScene.begin(); it != _staticObjectsInScene.end(); it++)
	{
		(*it)->Render(window);
	}
	for (std::vector<EngineObject*>::iterator it = _dynamicObjectsInScene.begin(); it != _dynamicObjectsInScene.end(); it++)
	{
		(*it)->Render(window);
	}
}

void Scene::Destroy()
{
	// destroy all objects in the scene
}

void Scene::SaveObject()
{
	// save all objects in the scene
}

void Scene::LoadObject()
{
	// load all objects in the scene
}