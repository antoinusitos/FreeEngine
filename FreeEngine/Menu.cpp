#include "Menu.h"
#include "ResourcesManager.h"
#include "Window.h"
#include "Input.h"
#include "EditorManager.h"
#include "SceneManager.h"
#include "Sound.h"
#include "CameraManager.h"
#include "FMath.h"
#include "ParticleSystem.h"

Menu::Menu() : Scene::Scene("Menu")
{
	name = "Menu";
	Debug::Instance().Print("new Scene" + name, DebugMessageType::DEBUGENGINE);

	_background = sf::RectangleShape(sf::Vector2f(0, 0));
	_background.setFillColor(sf::Color(80, 80, 80));
	_background.setPosition(0, 0);
	_font = ResourcesManager::Instance().GetFont("arial.ttf");
}

Menu::~Menu()
{
}

void Menu::PreAwake()
{
	Scene::PreAwake();

	Debug::Instance().Print("pre awake Menu", DebugMessageType::DEBUGENGINE);
  
	_maxIndex = 4;

	unsigned int windowSizeX = Window::Instance().GetScreenResolutionX();
	unsigned int windowSizeY = Window::Instance().GetScreenResolutionY();

	int tempY = windowSizeY / 4;
	int space = 80;

	_textNewGame.setString("New Game");
	_textLoadGame.setString("Load Game");
	_textOption.setString("Option");
	_textExit.setString("Quit");

	_allText.push_back(_textNewGame);
	_allText.push_back(_textLoadGame);
	_allText.push_back(_textOption);
	_allText.push_back(_textExit);

	for (std::vector<sf::Text>::iterator it = _allText.begin(); it < _allText.end(); it++)
	{
		(*it).setFont(_font);
		(*it).setCharacterSize(60);
		(*it).setFillColor(sf::Color::Red);
		(*it).setOrigin(((*it).getString().getSize() * (*it).getCharacterSize()) / 4, (*it).getString().getSize() / 2);
		(*it).setPosition((windowSizeX / 2), tempY);
		tempY += space;
	}

	_background.setFillColor(sf::Color(0, 114, 117));
}

void Menu::Awake()
{
	Scene::Awake();

	Debug::Instance().Print("Awake Menu", DebugMessageType::DEBUGENGINE);
}

void Menu::Start()
{
	Scene::Start();
	
	Debug::Instance().Print("Start Menu ", DebugMessageType::DEBUGENGINE);

	Sound* theme = new Sound();
	theme->InitMusic("theme.wav");
	theme->SetLoop(true);
	theme->Play();

	_allSounds.push_back(theme);

	_waitForFadeOut = false;
	_timer = 0;

	CameraManager::Instance().SetLocalOffset(FVector3());
	CameraManager::Instance().Move(Window::Instance().GetScreenResolutionX() / 2, Window::Instance().GetScreenResolutionY() / 2);
}

void Menu::Update(const float deltaTime)
{
	Scene::Update(deltaTime);

	if (_waitForFadeOut)
	{
		_timer += deltaTime;
		CameraManager::Instance().SetFade(FMath::Lerp(0, 255, _timer / _fadeDuration));
		if (_timer > _fadeDuration)
		{
			CameraManager::Instance().SetFade(255);
			ChangeIndex();
		}
		return;
	}

	if (_timer < _fadeDuration)
	{
		_timer += deltaTime;
		CameraManager::Instance().SetFade(FMath::Lerp(255, 0, _timer / _fadeDuration));
	}

	if (Input::Instance().GetKeyDown(KEYCODE::ARROWDOWN))
	{
		_currentIndex++;
		if (_currentIndex >= _maxIndex)
			_currentIndex = 0;
	}
	else if (Input::Instance().GetKeyDown(KEYCODE::ARROWUP))
	{
		_currentIndex--;
		if (_currentIndex < 0)
			_currentIndex = _maxIndex - 1 ;
	}
	else if (Input::Instance().GetKeyDown(KEYCODE::ENTER))
	{
		_waitForFadeOut = true;
		_timer = 0;
	}

	if (Input::Instance().GetKeyDown(KEYCODE::ESCAPE))
	{
		EditorManager::Instance().SetMustQuit();
	}

	RenderingWork();
}

void Menu::Render(sf::RenderWindow* window)
{
	Scene::Render(window);

	window->draw(_background);

	for (std::vector<sf::Text>::iterator it = _allText.begin(); it < _allText.end(); it++)
	{
		window->draw(*it);
	}
}

void Menu::ChangeIndex()
{
	if (_currentIndex == 0)
	{
		// NEW
		Debug::Instance().Print("Loading Scene : TestScene", DebugMessageType::DEBUGENGINE);
		SceneManager::Instance().LoadScene("TestScene", true);
	}
	else if (_currentIndex == 1)
	{
		// LOAD
	}
	else if (_currentIndex == 2)
	{
		// OPTIONS
	}
	else if (_currentIndex == 3)
	{
		// EXIT
		Debug::Instance().Print("Exit Menu !", DebugMessageType::DEBUGENGINE);
		EditorManager::Instance().SetMustQuit();
	}
	_currentIndex = 0;
}

void Menu::RenderingWork()
{
	for (std::vector<sf::Text>::iterator it = _allText.begin(); it < _allText.end(); it++)
	{
		(*it).setStyle(sf::Text::Regular);
		(*it).setOutlineThickness(0);
	}

	_allText.at(_currentIndex).setStyle(sf::Text::Bold);
	_allText.at(_currentIndex).setOutlineColor(sf::Color::White);
	_allText.at(_currentIndex).setOutlineThickness(5);

	unsigned int windowSizeX = Window::Instance().GetScreenResolutionX();
	unsigned int windowSizeY = Window::Instance().GetScreenResolutionY();

	_background.setSize(sf::Vector2f(windowSizeX, windowSizeY));
}

void Menu::Destroy()
{
	for (std::vector<Sound*>::iterator it = _allSounds.begin(); it != _allSounds.end(); ++it)
	{
		(*it)->Stop();
		delete (*it);
	}
	_allSounds.clear();
	_allText.clear();
	ClearDynamicObjects();
	ClearStaticObjects();
}