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

	AddString("Test Debug");

	AddToRendering();
}

DebugWindowLayout::~DebugWindowLayout()
{
}

void DebugWindowLayout::AddString(std::string newString)
{
	_allString.push_back(newString);
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(24);
	text.setString(sf::String(newString));
	text.setFillColor(sf::Color::Black);
	text.setPosition(_background->getPosition().x + 5, _background->getPosition().y);
	_allText.push_back(text);
}

void DebugWindowLayout::Render(sf::RenderWindow* SFMLWindow)
{
	WindowLayout::Render(SFMLWindow);

	for (std::vector<sf::Text>::iterator it = _allText.begin(); it != _allText.end(); ++it)
	{
		SFMLWindow->draw((*it));
	}
}