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

	void UpdateButton(const float deltaTime);

	void SetPosition(const float x, const float y);
	void SetPosition(const FVector2& position);
	void SetSize(const float x, const float y);
	void SetSize(const FVector2& size);

	void Render(sf::RenderWindow* SFMLWindow);

	void SetName(const std::string newName);

	void SetFont(const sf::Font newFont);

	void InitBackground();

	void SetActive(bool newState);

	void SetParent(ToolBarButton* newParent);

	const ToolBarButton* GetParent();

protected:

	bool _active;

	std::vector<ToolBarButton*> _subButtons;

	ToolBarButton* _parent;

	sf::RectangleShape _background;

	std::string _name;

	FVector2 _position;
	FVector2 _size;

	sf::Text _text;
	sf::Font _font;
};

