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

void EngineObject::Update(const float deltaTime)
{

}

void EngineObject::Render(const sf::RenderWindow* window)
{

}

void EngineObject::Destroy()
{

}

void EngineObject::DestroyObject()
{
	_beingDestroy = true;
	ObjectsManager::Instance().DestroyObject(this);
}

const void EngineObject::RegisterInObjectManager()
{
	ObjectsManager::Instance().RegisterEngineObject(this);
}