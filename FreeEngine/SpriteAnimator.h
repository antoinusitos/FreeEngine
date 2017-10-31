#pragma once

#include "Leaf.h"
#include <vector>

class SpriteAnimator : public Leaf
{
public:
	SpriteAnimator();
	~SpriteAnimator();

	void Start();
	void Update(float deltaTime);
	void Exit();
	void Awake();
	void Render(sf::RenderWindow* window);

	void AddTexture(std::string fileName);

	void SetColor(unsigned int r, unsigned int g, unsigned int b, unsigned int a);

	void SetPosition(float x, float y);

	void SetRotation(float angle);

	void SetScale(float x, float y);

	void SetOrigin(float x, float y);

	//TODO : cut the image to make multiples sub-images

private:
	sf::Sprite _sprite;
	std::vector<sf::Texture> _allTexture;
	int _currentFrame = 0;
	int _nbFrame = 0;

	sf::Color _color = sf::Color::White;

	//float _animRate = 1.f / 60.f;
	float _animRate = 0.1f;
	float _currentAnimTime = 0;
};

