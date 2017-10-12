#pragma once
#include "EngineObject.h"
#include "Transform.h"

class GameObject : public EngineObject
{
public:
	GameObject();
	~GameObject();

	void Start();

	void Update(float deltaTime);
	void Render();

	Transform transform;
};

