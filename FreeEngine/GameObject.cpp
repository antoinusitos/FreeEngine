#include "GameObject.h"
#include "Input.h"
#include <iostream>

GameObject::GameObject() : EngineObject()
{
	transform = Transform();
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