#include "Particle.h"
#include <iostream>
#include "FMath.h"

Particle::Particle()
{
	_transform = Transform();
	_startLifeTime = 2;
	_lifeTime = _startLifeTime;
}

Particle::~Particle()
{
}

void Particle::SetAcceleration(const FVector3& acceleration)
{
	_acceleration = acceleration;
}

void Particle::SetPosition(const FVector3& newPos)
{
	_transform.position = newPos;
}

void Particle::SetRotation(const FVector3& newRot)
{
	_transform.rotation = newRot;
}

void Particle::SetScale(const FVector3& newScale)
{
	_transform.scale = newScale;
}

void Particle::Init()
{
	_shape = sf::CircleShape(10);
	_color = sf::Color(0, 0, 0, 0);
	_shape.setFillColor(_color);
	_shape.setPosition(_transform.position.x, _transform.position.y);
	_shape.setScale(_transform.scale.x, _transform.scale.y);
}

void Particle::Update(float deltaTime)
{
	_velocity += _acceleration;
	_transform.position += _velocity;
	_shape.setPosition(_transform.position.x, _transform.position.y);

	if (_useScaleOverTime)
	{
		float current = FMath::Lerp(_beginScale, _endScale, 1 - _lifeTime / _startLifeTime);
		_shape.setScale(current, current);
	}
	else
	{
		_shape.setScale(_transform.scale.x, _transform.scale.y);
	}

	if (_colorOverLifeTime)
	{
		FVector4 col = FVector4::Lerp(_beginColor, _endColor,  1 -_lifeTime / _startLifeTime);
		_shape.setFillColor(sf::Color(col.x, col.y, col.z, col.w));
	}
	else
	{
		_color.a = (_lifeTime / _startLifeTime) * 255;
		_shape.setFillColor(_color);
	}

	_lifeTime -= deltaTime;
	if (_lifeTime <= 0)
	{
		_lifeTime = 0;
		_isDead = true;
	}
}

void Particle::Render(sf::RenderWindow* window)
{
	window->draw(_shape);
}

const bool Particle::GetIsDead()
{
	return _isDead;
}

void Particle::SetLifeTime(const float newTime)
{
	_lifeTime = newTime;
}

void Particle::SetColor(const int r, const int g, const int b, const int a = 255)
{
	_color = sf::Color(r, g, b, a);
	_shape.setFillColor(_color);
}

void Particle::SetColorOverTime(const FVector4& beginColor, const FVector4& endColor)
{
	_colorOverLifeTime = true;
	_beginColor = beginColor;
	_endColor = endColor;
	_color = sf::Color(_beginColor.x, _beginColor.y, _beginColor.z, _beginColor.w);
	_shape.setFillColor(_color);
}

void Particle::SetScaleOverTime(const float beginScale, const float endScale)
{
	_useScaleOverTime = true;
	_beginScale = beginScale;
	_endScale = endScale;
	_shape.setScale(_beginScale, _beginScale);
}