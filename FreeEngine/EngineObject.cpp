#include "EngineObject.h"
#include "ObjectsManager.h"

EngineObject::EngineObject()
{
	_ID = ObjectsManager::Instance().GetID();
	name = "Object" + std::to_string(_ID);
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
//	ObjectsManager::Instance().DestroyObject(this);
}

void EngineObject::RegisterInObjectManager()
{
	ObjectsManager::Instance().RegisterEngineObject(this);
}