#pragma once

#include <iostream>
#include <string>

#include "debug.h"

class EngineObject
{
public:
	EngineObject();
	~EngineObject();

	void PreAwake();
	virtual void Awake();
	virtual void Start();

	virtual void Update(float deltaTime);
	virtual void Render(sf::RenderWindow* window);

	virtual void Destroy();

	void DestroyObject();

	std::string name;

	void RegisterInObjectManager();

protected:
	int _ID = -1;

	bool _beingDestroy = false;
};

