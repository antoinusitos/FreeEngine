#pragma once

#include <iostream>
#include <string>

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

	virtual void Destroy();

	void DestroyObject();

	std::string name;

protected:
	int _ID = -1;
};

