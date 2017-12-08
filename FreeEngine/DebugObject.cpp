#include "DebugObject.h"

DebugObject::DebugObject()
{
}

DebugObject::~DebugObject()
{
}

void DebugObject::Awake()
{
}

void DebugObject::Start()
{
}

void DebugObject::Update(const float deltaTime)
{
	std::cout << transform.position.ToString() << '\n';
}

void DebugObject::Exit()
{
}

void DebugObject::Render(sf::RenderWindow * window)
{
}
