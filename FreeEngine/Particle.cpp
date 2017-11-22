#include "Particle.h"

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
	_shape.setFillColor(sf::Color(100, 250, 50));
	_shape.setPosition(_transform.position.x, _transform.position.y);
	_shape.setScale(_transform.scale.x, _transform.scale.y);
}

void Particle::Update(float deltaTime)
{
	_velocity += _acceleration;
	_transform.position += _velocity;
	_shape.setPosition(_transform.position.x, _transform.position.y);
	_shape.setScale(_transform.scale.x, _transform.scale.y);
	_lifeTime -= deltaTime;
	if (_lifeTime <= 0)
	{
		_lifeTime = 0;
		_isDead = true;
	}
	_color.a = (_lifeTime / _startLifeTime) * 255;
	_shape.setFillColor(_color);
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