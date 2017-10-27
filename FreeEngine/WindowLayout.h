#pragma once

#include <iostream>
#include <memory>
#include <mutex>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Window;

class WindowLayout
{
public:
	WindowLayout();
	~WindowLayout();

	//virtual void Render(std::unique_ptr<sf::RenderWindow> SFMLWindow);
	virtual void Render(sf::RenderWindow* SFMLWindow);

	void UnregisterToRendering();
protected:
	void AddToRendering();

	std::vector<sf::Drawable*> _allDrawable;
};

