#pragma once

#include <string>

class Component
{
public:
	Component();
	~Component();

	virtual void Start() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Exit() = 0;
	virtual void Awake() = 0;
	virtual void Render() = 0;

	bool isActive = true;
	std::string name;
};

