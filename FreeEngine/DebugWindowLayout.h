#pragma once

#include <string>

#include "WindowLayout.h"

class DebugWindowLayout : public WindowLayout
{
public:
	DebugWindowLayout();
	~DebugWindowLayout();

	void AddString(std::string newString);

	void Render(sf::RenderWindow* SFMLWindow);

	void Init();

	void Unregister();

private:
	sf::RectangleShape _background;

	float _debugZoneSizeY = 200.f;

	std::vector<sf::Text> _allText;
	sf::Font font;

	int _numberLogInConsole = 7;
	int _index = 0;
	float _beginY = 0;
	float _beginX = 0;
	float _incrementingY = 25;
};

