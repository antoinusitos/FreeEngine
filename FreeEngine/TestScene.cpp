#include "TestScene.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "InputLeaf.h"
#include "SceneManager.h"
#include "CameraManager.h"
#include "FMath.h"
#include "TestLeaf.h"
#include "GameManager.h"
#include "PauseMenu.h"
#include "UITransform.h"
#include "UIManager.h"
#include "DebugObject.h"

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
	_timer = 0;
	_transition = false;

	_pauseMenu = new PauseMenu();
	_pauseMenu->Init();

	go = new GameObject("go");
	background = new GameObject("background");
	foreground = new GameObject("foreground");
	life = new GameObject("life");

	go->transform.position = FVector3(60, 520, 1);
	go->transform.scale = FVector3(.75f, .75f, .75f);
	background->transform.position = FVector3(0, -300, 3);
	foreground->transform.position = FVector3(0, -300, 0);

	sr = new SpriteRenderer();
	sr->Init("Sprites/testSprite.png");
	go->AddComponent(sr);
	inputL = new InputLeaf();
	go->AddComponent(inputL);
	tl = new TestLeaf();
	go->AddComponent(tl);

	sr3 = new SpriteRenderer();
	sr3->Init("Sprites/Background_01/PARALLAX/background.png");
	sr4 = new SpriteRenderer();
	sr4->Init("Sprites/Background_01/PARALLAX/clouds.png");
	sr5 = new SpriteRenderer();
	sr5->Init("Sprites/Background_01/PARALLAX/rocks.png");
	background->AddComponent(sr3);
	background->AddComponent(sr4);
	background->AddComponent(sr5);

	sr6 = new SpriteRenderer();
	sr6->Init("Sprites/Background_01/PARALLAX/trees.png");
	foreground->AddComponent(sr6);
	_debugObject = new DebugObject();
	foreground->AddComponent(_debugObject);

	sr7 = new SpriteRenderer();
	sr7->Init("Sprites/testSprite2.png");
	life->AddComponent(sr7);
	uiTransform = new UITransform();
	life->AddComponent(uiTransform);
	UIManager::Instance().AddGameObjectToList(life);

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
	if (_transition) return;

	if (_timer < _fadeDuration)
	{
		_timer += deltaTime;
		CameraManager::Instance().SetFade(FMath::Lerp(255, 0, _timer / _fadeDuration));
		return;
	}

	if (GameManager::Instance().GetCurrentState() == GameState::PLAY)
	{
		Scene::Update(deltaTime);

		float x = CameraManager::Instance().GetCurrentX();
		float y = CameraManager::Instance().GetCurrentY();
		CameraManager::Instance().Move(
			FMath::Lerp(x, go->transform.position.x, deltaTime * _cameraSpeed),
			FMath::Lerp(y, go->transform.position.y, deltaTime * _cameraSpeed)
		);
	}

	UIManager::Instance().Update(deltaTime);
	_pauseMenu->Update(deltaTime);

	if (Input::Instance().GetKeyDown(KEYCODE::ESCAPE))
	{
		GameManager::Instance().ChangeCurrentState();
		if (GameManager::Instance().GetCurrentState() == GameState::PAUSE)
		{
			_pauseMenu->Active(true);
		}
		else
		{
			_pauseMenu->Active(false);
		}
	}

	if (Input::Instance().GetKeyDown(KEYCODE::SPACE))
	{
		RemoveDynamicObjectToScene(foreground);
		go->AddChild(foreground);
	}
}

void TestScene::Render(sf::RenderWindow* window)
{
	if (_transition) return;

	Scene::Render(window);

	UIManager::Instance().Render(window);

	_pauseMenu->Render(window);
}

void TestScene::Destroy()
{
	UIManager::Instance().EmptyGameObjectList();

	go->Exit();
	go->Destroy();
	go->DestroyObject();
	delete go;
	background->Exit();
	background->Destroy();
	background->DestroyObject();
	delete background;
	foreground->Exit();
	foreground->Destroy();
	foreground->DestroyObject();
	delete foreground;

	delete _pauseMenu;

	ClearDynamicObjects();
	ClearStaticObjects();

	_transition = false;
	_timer = 0;
	if (GameManager::Instance().GetCurrentState() == GameState::PAUSE)
	{
		GameManager::Instance().ChangeCurrentState();
	}
}