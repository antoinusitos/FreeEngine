#include "GameObject.h"
#include "Input.h"
#include <iostream>
#include "TagManager.h"

GameObject::GameObject(std::string Name) : EngineObject()
{
	name = Name;
	transform = Transform();
}

GameObject::GameObject() : EngineObject()
{
	name = "GameObject";
	transform = Transform();
}

GameObject::~GameObject()
{
}

void GameObject::Awake()
{
	EngineObject::Awake();

	for (std::vector<Leaf*>::iterator it = components.begin(); it != components.end(); ++it)
	{
		(*it)->Awake();
	}
}

void GameObject::Start()
{
	EngineObject::Start();

	for (std::vector<Leaf*>::iterator it = components.begin(); it != components.end(); ++it)
	{
		(*it)->Start();
	}
}

void GameObject::Update(float deltaTime)
{
	EngineObject::Update(deltaTime);

	if (Input::Instance().GetKeyPressed(KEYCODE::ARROWRIGHT))
	{
		transform.position.x += deltaTime * 2.0f;
		std::cout << "pos x : " << transform.position.x << std::endl;
	}

	for (std::vector<Leaf*>::iterator it = components.begin(); it != components.end(); ++it)
	{
		(*it)->Update(deltaTime);
	}
}

void GameObject::Render()
{
	EngineObject::Render();

	for (std::vector<Leaf*>::iterator it = components.begin(); it != components.end(); ++it)
	{
		(*it)->Render();
	}
}

void GameObject::Destroy()
{
	EngineObject::Destroy();
	
	for (std::vector<Leaf*>::iterator it = components.begin(); it != components.end(); ++it)
	{
		(*it)->Exit();
	}

	Debug::Instance().Print("Destroy object " + name, DebugMessageType::DEBUGLOG);

	DestroyObject();
}

void GameObject::AddTagToObject(std::string newTag)
{
	int newTagID = TagManager::Instance().GetTagID(newTag);

	if (newTagID == -1)
	{
		Debug::Instance().Print("Tag " + newTag + " does not exist. Add it first to the Tag Manager", DebugMessageType::DEBUGERROR);
		return;
	}

	_tags.push_back(newTagID);
}