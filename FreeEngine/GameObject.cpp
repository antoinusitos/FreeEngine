#include "GameObject.h"
#include "Input.h"
#include <iostream>

GameObject::GameObject(std::string Name) : EngineObject()
{
	name = Name;
	transform = Transform();
	Start();
}

GameObject::GameObject(bool InRunTime) : EngineObject()
{
	transform = Transform();
	if (InRunTime)
		Start();
}

GameObject::GameObject(std::string Name, bool InRunTime) : EngineObject()
{
	name = Name;
	transform = Transform();
	if(InRunTime)
		Start();
}

GameObject::~GameObject()
{
}

void GameObject::Start()
{
	EngineObject::Start();
}

void GameObject::Update(float deltaTime)
{
	EngineObject::Update(deltaTime);

	if (Input::GetInstance()->GetKeyPressed(KEY::ARROWRIGHT))
	{
		transform.position.x += deltaTime * 2.0f;
		std::cout << "pos x : " << transform.position.x << std::endl;
	}
}

void GameObject::Render()
{
	EngineObject::Render();
}

void GameObject::Destroy()
{
	EngineObject::Destroy();
	
	std::cout << "Destroy object" << name << std::endl;

	DestroyObject();
}
