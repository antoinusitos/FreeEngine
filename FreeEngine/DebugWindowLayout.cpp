#include "DebugWindowLayout.h"
#include "Window.h"

DebugWindowLayout::DebugWindowLayout()
{
	if (!font.loadFromFile("arial.ttf"))
	{
		std::cout << "Error : fail to load font arial.ttf" << std::endl;
	}

	_background = new sf::RectangleShape(sf::Vector2f(Window::GetInstance()->GetWindow()->getSize().x , _debugZoneSizeY));
	_background->setFillColor(sf::Color(153,153,153));
	_background->setPosition(0, Window::GetInstance()->GetWindow()->getSize().y - _debugZoneSizeY);
	_allDrawable.push_back(_background);

	_beginY = _background->getPosition().y;
	_beginX = _background->getPosition().x + 5;

	AddToRendering();
}

DebugWindowLayout::~DebugWindowLayout()
{
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