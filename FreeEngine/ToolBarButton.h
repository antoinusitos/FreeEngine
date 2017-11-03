#pragma once

#include <string>
#include "FVector2.h"
#include <SFML/Graphics.hpp>

class ToolBarButton
{
public:
	ToolBarButton();
	~ToolBarButton();

	virtual void Execute() = 0;

	void UpdateButton(float deltaTime);

	void SetPosition(float x, float y);
	void SetSize(float x, float y);

	void Render(sf::RenderWindow* SFMLWindow);

	void SetName(std::string newName);

	void SetFont(sf::Font newFont);

protected:
	std::string _name;

	FVector2 _position;
	FVector2 _size;

	sf::Text _text;
	sf::Font _font;
};

