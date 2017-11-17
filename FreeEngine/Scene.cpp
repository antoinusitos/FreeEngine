#include "Scene.h"
#include "FileHandler.h"
#include "GameObject.h"

Scene::Scene(const std::string name)
{
	_name = name;
	_fileName = "Assets/Scene/" + _name + ".txt";
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
	for (std::vector<GameObject*>::iterator it = _dynamicObjectsInScene.begin(); it != _dynamicObjectsInScene.end(); it++)
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
	for (std::vector<GameObject*>::iterator it = _dynamicObjectsInScene.begin(); it != _dynamicObjectsInScene.end(); it++)
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
	for (std::vector<GameObject*>::iterator it = _dynamicObjectsInScene.begin(); it != _dynamicObjectsInScene.end(); it++)
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
	for (int i = LAYERSNUMBER; i >= 0; i--)
	{
		for (std::vector<GameObject*>::iterator it = _dynamicObjectsInScene.begin(); it != _dynamicObjectsInScene.end(); it++)
		{
			if((*it)->transform.position.z == i)
				(*it)->Render(window);
		}
	}
}

void Scene::Destroy()
{
	// destroy all objects in the scene
}

void Scene::SaveObject()
{
	// save all objects in the scene
	std::cout << "write file " << _fileName << '\n';
	std::string toWrite = "";
	// Find a way to store objects and to save them
	FileHandler::Instance().WriteFile(_fileName, toWrite);
}

void Scene::LoadObject()
{
	// load all objects in the scene
	bool fileReadable = false;
	std::string allFiles = FileHandler::Instance().ReadFile(_fileName, &fileReadable);
	if (fileReadable)
	{
		// Find a way to store objects and to load them
	}
	else
	{
		Debug::Instance().Print("File " + _fileName + " not readable", DebugMessageType::DEBUGERROR);
	}
}

void Scene::AddDynamicObjectToScene(GameObject* newObject)
{
	_dynamicObjectsInScene.push_back(newObject);
}

void Scene::AddStaticObjectToScene(EngineObject* newObject)
{
	_staticObjectsInScene.push_back(newObject);
}

void Scene::SortDynamicObjects(int size)
{
	while (true)
	{
		
	}
}