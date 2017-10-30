#include "DebugWindowLayout.h"
#include "Window.h"
#include "Debug.h"
#include "ResourcesManager.h"

DebugWindowLayout::DebugWindowLayout()
{
	font = ResourcesManager::Instance().GetFont("arial.ttf");
}

DebugWindowLayout::~DebugWindowLayout()
{
}

void DebugWindowLayout::Init()
{
	_background = sf::RectangleShape(sf::Vector2f(Window::Instance().GetWindow()->getSize().x, _debugZoneSizeY));
	_background.setFillColor(sf::Color(153, 153, 153));
	_background.setPosition(0, Window::Instance().GetWindow()->getSize().y - _debugZoneSizeY);
	_allDrawable.push_back(&_background);

	_beginY = _background.getPosition().y;
	_beginX = _background.getPosition().x + 5;
       
	Window::Instance().AddRenderingLayout(this);
	
}

void DebugWindowLayout::Unregister()
{
	Window::Instance().RemoveRenderingLayout(this);
}

void DebugWindowLayout::AddString(DebugMessage debugMessage)
{
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(24);
	text.setString(debugMessage.message);
	switch (debugMessage.messageType)
	{
	case DebugMessageType::DEBUGLOG :
		text.setFillColor(sf::Color::Black);
		break;

	case DebugMessageType::DEBUGERROR :
		text.setFillColor(sf::Color::Red);
		break;

	case DebugMessageType::DEBUGWARNING :
		text.setFillColor(sf::Color::Yellow);
		break;
		 
	default:
		text.setFillColor(sf::Color::Black);
		break;
	}
	text.setPosition(_beginX, _beginY + _index * _incrementingY);
	_allText.push_back(text);
	_index++;
}

void DebugWindowLayout::Render(sf::RenderWindow* SFMLWindow)
{
	WindowLayout::Render(SFMLWindow);

	if (_active)
	{
		int tempIndex = 0;
		int startingIndex = 0;

		int size = _allText.size();
		if (size > _numberLogInConsole)
		{
			startingIndex = size - _numberLogInConsole;
		}

		for (std::vector<sf::Text>::iterator it = _allText.begin() + startingIndex; it != _allText.end(); ++it)
		{
			(*it).setPosition(_beginX, _beginY + tempIndex * _incrementingY);
			SFMLWindow->draw((*it));
			tempIndex++;
		}
	}
}
