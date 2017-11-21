#pragma once

#include "Scene.h"

class Sound;

class Menu : public Scene
{
public:
	Menu();
	~Menu();

	void PreAwake();
	void Awake();
	void Start();

	void Update(const float deltaTime);
	void Render(sf::RenderWindow* window);

	void Destroy();

private:
	int _currentIndex = 0;
	int _maxIndex = 0;

	sf::Font _font;

	sf::Text _textNewGame;
	sf::Text _textLoadGame;
	sf::Text _textOption;
	sf::Text _textExit;
	std::vector<sf::Text> _allText;

	sf::RectangleShape _background;

	std::vector<Sound*> _allSounds;
	
	void ChangeIndex();

	void RenderingWork();

	float _fadeDuration = 0.5f;
	float _timer = 0;

	float _waitForFadeOut = false;

};

