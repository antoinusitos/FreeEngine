#pragma once
#include "Leaf.h"
class DebugObject : public Leaf
{
public:
	DebugObject();
	~DebugObject();

	// Inherited via Leaf
	virtual void Awake();
	virtual void Start();
	virtual void Update(const float deltaTime);
	virtual void Exit();
	virtual void Render(sf::RenderWindow * window);
};

