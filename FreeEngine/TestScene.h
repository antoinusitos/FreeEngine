#pragma once

#include "Scene.h"

class GameObject;
class SpriteRenderer;
class InputLeaf;
class TestLeaf;
class PauseMenu;
class UITransform;
class DebugObject;

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

	void Destroy();

private:
	GameObject* go;
	GameObject* go2;
	GameObject* background;
	GameObject* foreground;
	GameObject* life;

	SpriteRenderer* sr;
	SpriteRenderer* sr2;
	SpriteRenderer* sr3;
	SpriteRenderer* sr4;
	SpriteRenderer* sr5;
	SpriteRenderer* sr6;
	SpriteRenderer* sr7;

	UITransform* uiTransform;

	InputLeaf* inputL;

	TestLeaf* tl;
	TestLeaf* tl2;

	PauseMenu* _pauseMenu = nullptr;

	DebugObject* _debugObject = nullptr;

	float _cameraSpeed = 1.5f;

	float _fadeDuration = 0.5f;
	float _timer = 0;

};

