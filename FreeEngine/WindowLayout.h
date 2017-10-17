#pragma once

#include <iostream>

#include "SFML\Graphics.hpp"
#include "SFML\System.hpp"

class Window;

class WindowLayout
{
public:
	WindowLayout();
	~WindowLayout();

	virtual void Render(sf::RenderWindow* SFMLWindow);

protected:
	void AddToRendering();

	std::vector<sf::Drawable*> _allDrawable;

};

