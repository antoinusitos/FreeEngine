#include "ToolBar.h"
#include "Window.h"
#include "Debug.h"
#include "ResourcesManager.h"
#include "ToolBarButton.h"
#include "MenuToolBarButton.h"


ToolBar::ToolBar()
{
	font = ResourcesManager::Instance().GetFont("arial.ttf");
}

ToolBar::~ToolBar()
{
	//delete menu;
}

void ToolBar::Init()
{
	_background = sf::RectangleShape(sf::Vector2f((float)Window::Instance().GetWindow()->getSize().x, _toolZoneSizeY));
	_background.setFillColor(sf::Color(153, 153, 153));
	_background.setPosition(0, 0);
	_allDrawable.push_back(&_background);

	menu = new MenuToolBarButton();
	menu->InitBackground();
	menu->SetFont(font);
	menu->SetName("Menu");
	menu->SetPosition(0, 0);
	menu->SetSize(80, 20);
	_allButton.push_back(menu);

	Window::Instance().AddRenderingLayout(this);
}

void ToolBar::Unregister()
{
	Window::Instance().RemoveRenderingLayout(this);
}

void ToolBar::Render(sf::RenderWindow* SFMLWindow)
{
	WindowLayout::Render(SFMLWindow);

	if (_active)
	{
		for (std::vector<ToolBarButton*>::iterator it = _allButton.begin(); it != _allButton.end(); ++it)
		{
			(*it)->Render(SFMLWindow);
		}
	}
}

void ToolBar::Update(const float deltaTime)
{
	WindowLayout::Update(deltaTime);

	if (_active)
	{
		for (std::vector<ToolBarButton*>::iterator it = _allButton.begin(); it != _allButton.end(); ++it)
		{
			(*it)->UpdateButton(deltaTime);
		}
	}
}