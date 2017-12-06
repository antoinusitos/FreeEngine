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

	void AddComponent(Component* newLeaf);
	void RemoveComponent(Component* leafToRemove);

	void AddChild(Composite* newChild);
	void RemoveChild(Composite* child);

	std::vector<Component*> components;
	std::vector<Composite*> children;
};

