#pragma once
#include "EngineObject.h"
#include "Transform.h"

class GameObject : public EngineObject
{
public:
	GameObject(std::string Name);
	GameObject(bool InRunTime);
	GameObject(std::string Name, bool InRunTime);
	~GameObject();

	void Start();

	void Update(float deltaTime);
	void Render();

	void Destroy();

	Transform transform;

	void AddTagToObject(std::string newTag);

private:
	std::vector<int> _tags;
};

