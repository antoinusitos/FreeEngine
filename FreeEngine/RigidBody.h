#pragma once

#include "Leaf.h"

class RigidBody : public Leaf
{
public:
	RigidBody();
	~RigidBody();

	virtual void Start();
	virtual void Update(const float deltaTime);
	virtual void Exit();
	virtual void Awake();
	virtual void Render();

	void SetUseGravity(bool newState);
	void SetCollide(bool newState);

private:
	bool _useGravity = true;
	bool _collide = true;
};

