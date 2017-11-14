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

	void Update(const float deltaTime);
	void Render(sf::RenderWindow* window);

	void Destroy();

	void Exit();

	void AddTagToObject(const std::string newTag);

	void SaveObject();
	void LoadObject();

private:
	std::vector<int> _tags;
};

