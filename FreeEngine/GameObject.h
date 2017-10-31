#pragma once
#include "EngineObject.h"
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
	void Render(sf::RenderWindow* window);

	void Destroy();

	void Exit();

	void AddTagToObject(std::string newTag);

private:
	std::vector<int> _tags;
};

