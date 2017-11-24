#include "PauseMenu.h"
#include "ResourcesManager.h"
#include "Window.h"
#include "Input.h"
#include "EditorManager.h"
#include "SceneManager.h"
#include "CameraManager.h"
#include "GameManager.h"

PauseMenu::PauseMenu()
{
}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::Init()
{
	_index = 0;

	int sizeX = Window::Instance().GetScreenResolutionX();
	int sizeY = Window::Instance().GetScreenResolutionY();

	_background = sf::RectangleShape();
	_background.setFillColor(sf::Color(0, 0, 0, 200));
	_background.setSize(sf::Vector2f(sizeX, sizeY));
	_background.setPosition(0, 0);

	float x = CameraManager::Instance().GetCurrentX();
	float y = CameraManager::Instance().GetCurrentY();

	_font = ResourcesManager::Instance().GetFont("arial.ttf");

	_resumeText = sf::Text();
	_backMenuText = sf::Text();
	_quitText = sf::Text();

	_resumeText.setString("Resume Game");
	_backMenuText.setString("Back to Menu");
	_quitText.setString("Quit Game");

	_resumeText.setFont(_font);
	_backMenuText.setFont(_font);
	_quitText.setFont(_font);

	_resumeText.setCharacterSize(60);
	_backMenuText.setCharacterSize(60);
	_quitText.setCharacterSize(60);

	_resumeText.setFillColor(sf::Color::Red);
	_backMenuText.setFillColor(sf::Color::Red);
	_quitText.setFillColor(sf::Color::Red);

	_resumeText.setOrigin((_resumeText.getString().getSize() * _resumeText.getCharacterSize()) / 4, _resumeText.getString().getSize() / 2);
	_backMenuText.setOrigin((_backMenuText.getString().getSize() * _backMenuText.getCharacterSize()) / 4, _backMenuText.getString().getSize() / 2);
	_quitText.setOrigin((_quitText.getString().getSize() * _quitText.getCharacterSize()) / 4, _quitText.getString().getSize() / 2);

	_resumeText.setPosition(x - _resumeText.getString().getSize() / 2, y - 70);
	_backMenuText.setPosition(x - _backMenuText.getString().getSize() / 2, y);
	_quitText.setPosition(x - _quitText.getString().getSize() / 2, y + 70);
}

void PauseMenu::Active(bool newState)
{
	_active = newState;
	_index = 0;
}

void PauseMenu::Update(const float deltaTime)
{
	if (_active)
	{
		if (Input::Instance().GetKeyDown(KEYCODE::ARROWDOWN))
		{
			_index++;
			if (_index > 2)
				_index = 0;
		}
		else if (Input::Instance().GetKeyDown(KEYCODE::ARROWUP))
		{
			_index--;
			if (_index < 0)
				_index = 2;
		}

		if (Input::Instance().GetKeyDown(KEYCODE::ENTER))
		{
			ChangeIndex();
		}

	}

	RenderingWork();
}

void PauseMenu::Render(sf::RenderWindow* window)
{
	if (_active)
	{
		window->draw(_background);
		window->draw(_resumeText);
		window->draw(_backMenuText);
		window->draw(_quitText);
	}
}

void PauseMenu::ChangeIndex()
{
	if (_index == 0)
	{
		// RESUME
		Active(false);
		GameManager::Instance().ChangeCurrentState();
	}
	else if (_index == 1)
	{
		// MENU
		SceneManager::Instance().LoadScene("Menu", true);
	}
	else if (_index == 2)
	{
		// QUIT
		EditorManager::Instance().SetMustQuit();
	}
}

void PauseMenu::RenderingWork()
{
	float x = CameraManager::Instance().GetCurrentX();
	float y = CameraManager::Instance().GetCurrentY();

	int sizeX = Window::Instance().GetScreenResolutionX();
	int sizeY = Window::Instance().GetScreenResolutionY();

	_resumeText.setPosition(x - _resumeText.getString().getSize() / 2, y - 70);
	_backMenuText.setPosition(x - _backMenuText.getString().getSize() / 2, y);
	_quitText.setPosition(x - _quitText.getString().getSize() / 2, y  + 70);

	_resumeText.setStyle(sf::Text::Regular);
	_resumeText.setOutlineThickness(0);
	_backMenuText.setStyle(sf::Text::Regular);
	_backMenuText.setOutlineThickness(0);
	_quitText.setStyle(sf::Text::Regular);
	_quitText.setOutlineThickness(0);

	if (_index == 0)
	{
		_resumeText.setStyle(sf::Text::Bold);
		_resumeText.setOutlineColor(sf::Color::White);
		_resumeText.setOutlineThickness(5);
	}
	else if (_index == 1)
	{
		_backMenuText.setStyle(sf::Text::Bold);
		_backMenuText.setOutlineColor(sf::Color::White);
		_backMenuText.setOutlineThickness(5);
	}
	else if (_index == 2)
	{
		_quitText.setStyle(sf::Text::Bold);
		_quitText.setOutlineColor(sf::Color::White);
		_quitText.setOutlineThickness(5);
	}

	_background.setPosition(x - sizeX / 2, y - sizeY / 2);

	_background.setSize(sf::Vector2f(sizeX, sizeY));
}