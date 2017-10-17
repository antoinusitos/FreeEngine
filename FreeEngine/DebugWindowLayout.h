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

private:
	sf::RectangleShape* _background;

	float _debugZoneSizeY = 200.f;

	std::vector<std::string> _allString;
	std::vector<sf::Text> _allText;
	sf::Font font;
};

