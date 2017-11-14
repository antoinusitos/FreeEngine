#pragma once

#include <string>
#include "Window.h"

class Component
{
public:
	Component();
	~Component();

	virtual void Start() = 0;
	virtual void Update(const float deltaTime) = 0;
	virtual void Exit() = 0;
	virtual void Awake() = 0;
	virtual void Render(sf::RenderWindow* window) = 0;

	bool isActive = true;
};

