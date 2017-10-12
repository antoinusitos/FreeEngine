#include "ObjectsManager.h"
#include "EngineObject.h"


EngineObject::EngineObject()
{
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