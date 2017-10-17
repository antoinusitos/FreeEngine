#include "ObjectsManager.h"

EngineObject::EngineObject()
{
	_ID = ObjectsManager::GetInstance()->GetID();
	name = "Object" + std::to_string(_ID);
	ObjectsManager::GetInstance()->RegisterEngineObject(this);
}

EngineObject::~EngineObject()
{

}

void EngineObject::PreAwake()
{
	
}

void EngineObject::Awake()
{

}

void EngineObject::Start()
{
}

void EngineObject::Update(float deltaTime)
{

}

void EngineObject::Render()
{

}

void EngineObject::Destroy()
{

}

void EngineObject::DestroyObject()
{
	_beingDestroy = true;
	ObjectsManager::GetInstance()->DestroyObject(this);
}