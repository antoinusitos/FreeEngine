#pragma once

#include "Leaf.h"
#include "Input.h"

class InputLeaf : public Leaf
{
public:
	InputLeaf();
	~InputLeaf();

	void Start();
	void Update(const float deltaTime);
	void Exit();
	void Awake();
	void Render(sf::RenderWindow* window);
};

