#include "TestScene.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "InputLeaf.h"
#include "SceneManager.h"

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

}

void TestScene::Render(sf::RenderWindow* window)
{
	Scene::Render(window);
}