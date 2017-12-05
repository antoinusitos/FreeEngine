#pragma once

#include "Component.h"
#include "Leaf.h"

#include "Transform.h"
#include <vector>

class Composite : public Component
{
public:
	Composite();
	~Composite();

	virtual void Start() = 0;
	virtual void Update(const float deltaTime) = 0;
	virtual void Exit() = 0;
	virtual void Awake() = 0;
	virtual void Render(sf::RenderWindow* window) = 0;

	void AddLeaf(Leaf* newLeaf);
	void RemoveLeaf(Leaf* leafToRemove);

	std::vector<Leaf*> components;

	Transform transform;
};

