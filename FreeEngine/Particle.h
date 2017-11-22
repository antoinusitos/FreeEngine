#pragma once

#include "SFML\Graphics.hpp"
#include "FVector3.h"
#include "Transform.h"

class Particle
{
public:
	Particle();
	~Particle();

	void SetAcceleration(const FVector3& acceleration);
	void SetPosition(const FVector3& newPos);
	void SetRotation(const FVector3& newRot);
	void SetScale(const FVector3& newScale);

	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);

	void Init();

	const bool GetIsDead();

	void SetLifeTime(const float newTime);

	void SetColor(const int r, const int g, const int b, const int a);

private:
	FVector3 _velocity;
	FVector3 _acceleration;
	Transform _transform;

	sf::Sprite _sprite;
	sf::Texture _texture;

	float _lifeTime = 0;
	float _startLifeTime = 0;

	bool _isDead = false;

	sf::Color _color = sf::Color(100, 250, 50, 255);

	//TEST
	sf::CircleShape _shape;
};

