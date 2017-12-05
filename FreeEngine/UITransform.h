#pragma once

#include "Leaf.h"
#include "FVector3.h"

class UITransform : public Leaf
{
public:
	UITransform();
	~UITransform();

	void Awake();
	void Start();
	void Update(const float deltaTime);
	void Render(sf::RenderWindow* window);
	void Exit();

	// offset;
	FVector3 offset = FVector3();
};