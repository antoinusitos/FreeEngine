#pragma once

#include "Leaf.h"
#include <iostream>

class TestLeaf : public Leaf
{
public:
	TestLeaf();
	~TestLeaf();

	virtual void Start();
	virtual void Update(const float deltaTime);
	virtual void Exit();
	virtual void Awake();
	virtual void Render();
};

