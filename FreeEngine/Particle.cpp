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

void Particle::ApplyForce(const FVector3& force)
{
	FVector3 f = force;
	f /= _mass;
	_acceleration += f;
}

void Particle::Update(float deltaTime)
{
	_velocity += _acceleration;
	_transform.position += _velocity;
	_acceleration *= 0;

	if (_useScaleOverTime)
	{
		float current = FMath::Lerp(_beginScale, _endScale, 1 - _lifeTime / _startLifeTime);
		if (_useTexture)
		{
			_sprite.setScale(current, current);
		}
		else
		{
			_shape.setScale(current, current);
		}
	}
	else
	{
		_shape.setScale(_transform.scale.x, _transform.scale.y);
	}

	if (_colorOverLifeTime)
	{
		FVector4 col = FVector4::Lerp(_beginColor, _endColor,  1 -_lifeTime / _startLifeTime);
		_color = sf::Color(col.x, col.y, col.z, col.w);
	}
	else
	{
		_color.a = (_lifeTime / _startLifeTime) * 255;
	}

	if (_useTexture)
	{
		_sprite.setColor(_color);
	}
	else
	{
		_shape.setFillColor(_color);
	}

	if (_useTexture)
	{
		_sprite.setPosition(_transform.position.x, _transform.position.y);
		_sprite.setScale(_transform.scale.x, _transform.scale.y);
	}
	else
	{
		_shape.setPosition(_transform.position.x, _transform.position.y);
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
	if (_useTexture)
	{
		window->draw(_sprite);
	}
	else
	{
		window->draw(_shape);
	}
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

void Particle::SetTexture(sf::Texture newTexture)
{
	_useTexture = true;
	_texture = newTexture;
	_sprite.setTexture(_texture);
}

void Particle::SetUseGravity(float mass)
{
	_mass = mass;
}