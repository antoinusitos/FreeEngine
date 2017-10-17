#pragma once

#include <iostream>
#include <memory>
#include <mutex>

#include "SFML\Graphics.hpp"
#include "SFML\System.hpp"

class Window;

class WindowLayout
{
public:
	WindowLayout();
	~WindowLayout();

	virtual void Render(std::shared_ptr<sf::RenderWindow> SFMLWindow);

protected:
	void AddToRendering();

	std::vector<std::shared_ptr<sf::Drawable>> _allDrawable;
	int lol;
};

