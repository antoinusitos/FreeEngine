#pragma once

#include <string>

#include "WindowLayout.h"
#include "Data.h"
#include "FileHandler.h"
#include "FVector3.h"

class DebugWindowLayout : public WindowLayout, public FileObserver
{
public:
	DebugWindowLayout();
	~DebugWindowLayout();

	void AddString(const DebugMessage debugMessage);

	void Render(sf::RenderWindow* SFMLWindow);

	void Update(const float deltaTime);

	void Init();

	void Unregister();

	void NotifyChange();

	void SetOpen(const bool newState);

	void HandleConsoleWord();

private:
	sf::RectangleShape _background;

	float _debugZoneSizeY = 200.f;
	float _sizeX = 0;
	float _consoleSpeed = 0.5f;
	float _posY = 0; // relative for the animation
	float _progress = 0;

	const std::string configFileName = "Assets/Config/Engine.txt";

	bool _opening = false;
	bool _direction = true;

	std::vector<sf::Text> _allText;
	sf::Font font;

	int _numberLogInConsole = 7;
	int _index = 0;
	float _beginY = 5;
	float _beginX = 5;
	float _incrementingY = 25;

	float _positionX = 0;
	float _positionY = 0;

	FVector3 _color;

	void HandleDataChanges();

	std::vector<EngineData> _allEngineData;

	std::string _currentDebugstring = "";
	bool _isInput = false;
	sf::Text _debugStringText;
};

