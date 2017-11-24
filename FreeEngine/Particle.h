#pragma once

#include "SFML\Graphics.hpp"
#include "FVector3.h"
#include "FVector4.h"
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

	void SetColorOverTime(const FVector4& beginColor, const FVector4& endColor);

	void SetScaleOverTime(const float beginScale, const float endScale);

	void SetTexture(sf::Texture newTexture);

	void SetUseGravity(float mass = 1);

	void ApplyForce(const FVector3& force);

private:
	FVector3 _velocity;
	FVector3 _acceleration;
	Transform _transform;

	bool _useTexture = false;
	sf::Sprite _sprite;
	sf::Texture _texture;

	float _lifeTime = 0;
	float _startLifeTime = 0;

	bool _isDead = false;

	sf::Color _color = sf::Color(255, 255, 255, 255);

	bool _colorOverLifeTime = false;
	FVector4 _beginColor = FVector4();
	FVector4 _endColor = FVector4();

	bool _useScaleOverTime = false;
	float _beginScale = 0;
	float _endScale = 0;

	float _mass = 1;

	//TEST
	sf::CircleShape _shape;
};

