#pragma once

#include "Scene.h"

class GameObject;
class SpriteRenderer;
class InputLeaf;
class TestLeaf;

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

	TestLeaf* tl;

	float _cameraSpeed = 1.5f;

	float _fadeDuration = 0.5f;
	float _timer = 0;
};

