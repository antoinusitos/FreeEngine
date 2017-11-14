#pragma once

#include "Leaf.h"
#include <vector>

class SpriteAnimator : public Leaf
{
public:
	SpriteAnimator();
	~SpriteAnimator();

	void Start();
	void Update(const float deltaTime);
	void Exit();
	void Awake();
	void Render(sf::RenderWindow* window);

	void AddTexture(const std::string fileName);

	void SetColor(const unsigned int r, const unsigned int g, const unsigned int b, const unsigned int a);

	void SetPosition(const float x, const float y);

	void SetRotation(const float angle);

	void SetScale(const float x, const float y);

	void SetOrigin(const float x, const float y);

	void SetAnimationSpeed(const float newSpeed);

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

	float _animationSpeed = 1.0f;
};

