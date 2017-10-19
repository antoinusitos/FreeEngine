#include "DebugWindowLayout.h"
#include "Window.h"
#include "Debug.h"

DebugWindowLayout::DebugWindowLayout()
{
	if (!font.loadFromFile("arial.ttf"))
	{
		Debug::Instance().Print("Error : fail to load font arial.ttf" + '\n');
	}
}

DebugWindowLayout::~DebugWindowLayout()
{
	//WindowLayout::~WindowLayout();

	//_allDrawable.erase(_allDrawable.begin(), _allDrawable.end());
	//_allText.erase(_allText.begin(), _allText.end());

	//UnregisterToRendering();

}

void DebugWindowLayout::Init()
{
	_background = sf::RectangleShape(sf::Vector2f(Window::Instance().GetWindow()->getSize().x, _debugZoneSizeY));
	_background.setFillColor(sf::Color(153, 153, 153));
	_background.setPosition(0, Window::Instance().GetWindow()->getSize().y - _debugZoneSizeY);
	_allDrawable.push_back(&_background);

	_beginY = _background.getPosition().y;
	_beginX = _background.getPosition().x + 5;

	AddToRendering();
}

void DebugWindowLayout::AddString(std::string newString)
{
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(24);
	text.setString(sf::String(newString));
	text.setFillColor(sf::Color::Black);
	text.setPosition(_beginX, _beginY + _index * _incrementingY);
	_allText.push_back(text);
	_index++;
}

void DebugWindowLayout::Render(sf::RenderWindow* SFMLWindow)
{
	WindowLayout::Render(SFMLWindow);

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