#pragma once

#include "Component.h"
#include "Leaf.h"

#include <vector>

class Composite : public Component
{
public:
	Composite();
	~Composite();

	virtual void Start() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Exit() = 0;
	virtual void Awake() = 0;
	virtual void Render() = 0;

	std::vector<Leaf*> components;

	void AddLeaf(Leaf* newLeaf);
	void RemoveLeaf(Leaf* leafToRemove);
};

