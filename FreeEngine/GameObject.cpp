#include "GameObject.h"
#include "Input.h"
#include <iostream>
#include "TagManager.h"
#include "ObjectsManager.h"
#include "SaveManager.h"

GameObject::GameObject(std::string Name) : EngineObject()
{
	_ID = ObjectsManager::Instance().GetID();
	name = Name;
	transform = Transform();
}

GameObject::GameObject() : EngineObject()
{
	_ID = ObjectsManager::Instance().GetID();
	name = "GameObject"+ std::to_string(_ID);
	transform = Transform();
}

GameObject::~GameObject()
{
}

void GameObject::Awake()
{
	EngineObject::Awake();
	Composite::Awake();
}

void GameObject::Start()
{
	EngineObject::Start();
	Composite::Start();
}

void GameObject::Update(const float deltaTime)
{
	EngineObject::Update(deltaTime);
	Composite::Update(deltaTime);
}

void GameObject::Render(sf::RenderWindow* window)
{
	EngineObject::Render(window);
	Composite::Render(window);
}

void GameObject::Destroy()
{
	EngineObject::Destroy();

	Debug::Instance().Print("Destroy object " + name, DebugMessageType::DEBUGLOG);

	DestroyObject();
}

void GameObject::Exit()
{
	Composite::Exit();
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

void GameObject::SaveObject()
{
	//TODO : save All composites

	SaveManager::Instance().SetFloat("lol", 32.0f);
	SaveManager::Instance().SetTransform("transform", &transform);
}

void GameObject::LoadObject()
{
	bool hasRecover = false;
	float fRecover = -1;
	fRecover = SaveManager::Instance().GetFloat("lol", &hasRecover);
	if(hasRecover)
		std::cout << "fRecover=" << fRecover << '\n';
	hasRecover = false;
	Transform t = SaveManager::Instance().GetTransform("transform", &hasRecover);
	if (hasRecover)
	{
		transform = t;
		std::cout << "transform=" << transform.ToString() << '\n';
	}
}