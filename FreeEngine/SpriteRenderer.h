#pragma once

#include "Leaf.h"
#include <iostream>
#include "SFML\Graphics.hpp"

class SpriteRenderer : public Leaf
{
public:
	SpriteRenderer();
	~SpriteRenderer();

	void Init(std::string path);
	sf::Sprite GetSprite();
	sf::Texture GetTexture();

	void SetSmooth(bool newState);
	void SetRepeat(bool newState);

	void SetColor(unsigned int r, unsigned int g, unsigned int b, unsigned int a);

	void SetPosition(float x, float y);

	void SetRotation(float angle);

	void SetScale(float x, float y);

	void SetOrigin(float x, float y);

	void Start();
	void Update(float deltaTime);
	void Exit();
	void Awake();
	void Render(sf::RenderWindow* window);

private:
	sf::Sprite _sprite;
	sf::Texture _texture;
	std::string _path;

	bool _smooth = true;
	bool _repeat = false;

	sf::Color _color = sf::Color::White;
};

