#pragma once

#include "SFML\Graphics.hpp"
#include "SFML\System.hpp" //TODO : Watch that to include Vector2 !!

class EngineVisual
{
public:
	EngineVisual();
	~EngineVisual();

	void Render();

private:
	sf::RectangleShape DebugConsole;
};

