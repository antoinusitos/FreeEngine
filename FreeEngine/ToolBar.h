#pragma once

#include "WindowLayout.h"

class ToolBarButton;
class MenuToolBarButton;

class ToolBar : public WindowLayout
{
public:
	ToolBar();
	~ToolBar();

	void Init();

	void Render(sf::RenderWindow* SFMLWindow);

	void Update(const float deltaTime);

	void Unregister();

private:
	sf::RectangleShape _background;

	float _toolZoneSizeY = 20.0f;

	std::vector<ToolBarButton*> _allButton;
	sf::Font font;

	MenuToolBarButton* menu;
};

