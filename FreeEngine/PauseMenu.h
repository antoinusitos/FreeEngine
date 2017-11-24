#pragma once

#include "SFML\Graphics.hpp"

class PauseMenu
{
public:
	PauseMenu();
	~PauseMenu();

	void Init();
	void Active(bool newState);

	void Update(const float deltaTime);
	void Render(sf::RenderWindow* window);

	void ChangeIndex();

	void RenderingWork();

private:
	sf::RectangleShape _background;
	sf::Text _resumeText;
	sf::Text _backMenuText;
	sf::Text _quitText;

	sf::Font _font;

	int _index = 0;
	bool _active = false;
};

