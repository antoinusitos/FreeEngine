#include "Menu.h"
#include "ResourcesManager.h"
#include "Window.h"
#include "Input.h"

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

}

void Menu::Awake()
{
	Scene::Awake();
}

void Menu::Start()
{
	Scene::Start();

}

void Menu::Update(const float deltaTime)
{
	Scene::Update(deltaTime);

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

	for (std::vector<sf::Text>::iterator it = _allText.begin(); it < _allText.end(); it++)
	{
		(*it).setStyle(sf::Text::Regular);
		(*it).setOutlineThickness(0);
	}

	_allText.at(_currentIndex).setStyle(sf::Text::Bold);
	_allText.at(_currentIndex).setOutlineColor(sf::Color::White);
	_allText.at(_currentIndex).setOutlineThickness(1);
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

}