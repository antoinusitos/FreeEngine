#include "RigidBody.h"

RigidBody::RigidBody()
{
}

RigidBody::~RigidBody()
{
}

void RigidBody::Awake()
{
}

void RigidBody::Start()
{
}

void RigidBody::Update(const float deltaTime)
{
	if (_useGravity)
	{
		// apply gravity
	}
}

void RigidBody::Exit()
{
}

void RigidBody::Render()
{
}

void RigidBody::SetUseGravity(bool newState)
{
	_useGravity = newState;
}

void RigidBody::SetCollide(bool newState)
{
	_collide = newState;
}