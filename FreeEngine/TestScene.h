#pragma once

#include "Scene.h"

class GameObject;
class SpriteRenderer;
class InputLeaf;

class TestScene : public Scene
{
public:
	TestScene();
	~TestScene();

	void PreAwake();
	void Awake();
	void Start();

	void Update(const float deltaTime);
	void Render(sf::RenderWindow* window);

private:
	GameObject* go;
	GameObject* background;
	GameObject* foreground;

	SpriteRenderer* sr;
	SpriteRenderer* sr3;
	SpriteRenderer* sr4;
	SpriteRenderer* sr5;
	SpriteRenderer* sr6;

	InputLeaf* inputL;
};

