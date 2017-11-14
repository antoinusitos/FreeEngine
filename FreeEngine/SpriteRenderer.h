#pragma once

#include "Leaf.h"
#include <iostream>
#include "SFML\Graphics.hpp"

class SpriteRenderer : public Leaf
{
public:
	SpriteRenderer();
	~SpriteRenderer();

	void Init(const std::string path);
	const sf::Sprite GetSprite();
	const sf::Texture GetTexture();

	void SetSmooth(const bool newState);
	void SetRepeat(const bool newState);

	void SetColor(const unsigned int r, const unsigned int g, const unsigned int b, const unsigned int a);

	void SetPosition(const float x, const float y);

	void SetRotation(const float angle);

	void SetScale(const float x, const float y);

	void SetOrigin(const float x, const float y);

	void Start();
	void Update(const float deltaTime);
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

