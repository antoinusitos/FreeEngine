#include "TestScene.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "InputLeaf.h"
#include "SceneManager.h"
#include "CameraManager.h"
#include "FMath.h"
#include "TestLeaf.h"

TestScene::TestScene() : Scene::Scene("TestScene")
{
	name = "TestScene";
	Debug::Instance().Print("new Scene" + name, DebugMessageType::DEBUGENGINE);
}

TestScene::~TestScene()
{
}

void TestScene::PreAwake()
{
	go = new GameObject("go");
	background = new GameObject("background");
	foreground = new GameObject("foreground");

	go->transform.position = FVector3(60, 520, 1);
	go->transform.scale = FVector3(.75f, .75f, .75f);
	background->transform.position = FVector3(0, -300, 3);
	foreground->transform.position = FVector3(0, -300, 0);

	sr = new SpriteRenderer();
	sr->Init("Sprites/testSprite.png");
	go->AddLeaf(sr);
	inputL = new InputLeaf();
	go->AddLeaf(inputL);
	tl = new TestLeaf();
	go->AddLeaf(tl);

	sr3 = new SpriteRenderer();
	sr3->Init("Sprites/Background_01/PARALLAX/background.png");
	sr4 = new SpriteRenderer();
	sr4->Init("Sprites/Background_01/PARALLAX/clouds.png");
	sr5 = new SpriteRenderer();
	sr5->Init("Sprites/Background_01/PARALLAX/rocks.png");
	background->AddLeaf(sr3);
	background->AddLeaf(sr4);
	background->AddLeaf(sr5);

	sr6 = new SpriteRenderer();
	sr6->Init("Sprites/Background_01/PARALLAX/trees.png");
	foreground->AddLeaf(sr6);

	AddDynamicObjectToScene(go);
	AddDynamicObjectToScene(foreground);

	AddStaticObjectToScene(background);
}

void TestScene::Awake()
{
	Scene::Awake();
}

void TestScene::Start()
{
	Scene::Start();
}

void TestScene::Update(const float deltaTime)
{
	Scene::Update(deltaTime);

	if (_timer < _fadeDuration)
	{
		_timer += deltaTime;
		CameraManager::Instance().SetFade(FMath::Lerp(255, 0, _timer / _fadeDuration));
	}

	float x = CameraManager::Instance().GetCurrentX();
	float y = CameraManager::Instance().GetCurrentY();
	CameraManager::Instance().Move(
		FMath::Lerp(x, go->transform.position.x, deltaTime * _cameraSpeed), 
		FMath::Lerp(y, go->transform.position.y, deltaTime * _cameraSpeed)
	);
}

void TestScene::Render(sf::RenderWindow* window)
{
	Scene::Render(window);
}