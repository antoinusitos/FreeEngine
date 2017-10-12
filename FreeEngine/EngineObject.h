#pragma once
#include <iostream>

class EngineObject
{
public:
	EngineObject();
	~EngineObject();

	void PreAwake();
	virtual void Awake();
	virtual void Start();

	virtual void Update(float deltaTime);
	virtual void Render();
};

