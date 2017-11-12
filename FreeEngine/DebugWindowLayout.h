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

	void AddString(DebugMessage debugMessage);

	void Render(sf::RenderWindow* SFMLWindow);

	void Update(float deltaTime);

	void Init();

	void Unregister();

	void NotifyChange();

	void SetOpen(bool newState);

private:
	sf::RectangleShape _background;

	float _debugZoneSizeY = 200.f;
	float _consoleSpeed = 0.5f;
	float _posY = 0;
	float _progress = 0;

	std::string configFileName = "Assets/Config/Engine.txt";

	bool _opening = false;
	bool _direction = true;

	std::vector<sf::Text> _allText;
	sf::Font font;

	int _numberLogInConsole = 7;
	int _index = 0;
	float _beginY = 0;
	float _beginX = 0;
	float _incrementingY = 25;

	FVector3 _color;

	void HandleDataChanges();

	std::vector<EngineData> _allEngineData;
};

