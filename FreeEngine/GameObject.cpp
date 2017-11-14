#include "GameObject.h"
#include "Input.h"
#include <iostream>
#include "TagManager.h"
#include "ObjectsManager.h"

GameObject::GameObject(std::string Name) : EngineObject()
{
	_ID = ObjectsManager::Instance().GetID();
	name = Name;
	transform = Transform();
	ObjectsManager::Instance().RegisterEngineObject(this);
}

GameObject::GameObject() : EngineObject()
{
	_ID = ObjectsManager::Instance().GetID();
	name = "GameObject"+ std::to_string(_ID);
	transform = Transform();
	ObjectsManager::Instance().RegisterEngineObject(this);
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

void GameObject::Update(const float deltaTime)
{
	EngineObject::Update(deltaTime);

	//------TEST------
	if (Input::Instance().GetKeyPressed(KEYCODE::ARROWRIGHT))
		transform.position.x += deltaTime * 100.0f;
	else if (Input::Instance().GetKeyPressed(KEYCODE::ARROWLEFT))
		transform.position.x -= deltaTime * 100.0f;

	if (Input::Instance().GetKeyPressed(KEYCODE::ARROWDOWN))
		transform.position.y += deltaTime * 100.0f;
	else if (Input::Instance().GetKeyPressed(KEYCODE::ARROWUP))
		transform.position.y -= deltaTime * 100.0f;
	//------TEST------

	for (std::vector<Leaf*>::iterator it = components.begin(); it != components.end(); ++it)
	{
		(*it)->Update(deltaTime);
	}
}

void GameObject::Render(const sf::RenderWindow* window)
{
	EngineObject::Render(window);

	for (std::vector<Leaf*>::iterator it = components.begin(); it != components.end(); ++it)
	{
		(*it)->Render(window);
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

void GameObject::Exit()
{

}

void GameObject::AddTagToObject(const std::string newTag)
{
	int newTagID = TagManager::Instance().GetTagID(newTag);

	if (newTagID == -1)
	{
		Debug::Instance().Print("Tag " + newTag + " does not exist. Add it first to the Tag Manager", DebugMessageType::DEBUGERROR);
		return;
	}

	_tags.push_back(newTagID);
}