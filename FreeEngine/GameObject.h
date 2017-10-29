#pragma once
#include "EngineObject.h"
#include "Transform.h"
#include "Composite.h"

class GameObject : public EngineObject, public Composite
{
public:
	GameObject(std::string Name);
	GameObject();
	~GameObject();

	void Awake();

	void Start();

	void Update(float deltaTime);
	void Render();

	void Destroy();

	Transform transform;

	void AddTagToObject(std::string newTag);

private:
	std::vector<int> _tags;
};

