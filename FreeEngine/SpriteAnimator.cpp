#include "SpriteAnimator.h"
#include "ResourcesManager.h"
#include "Composite.h"

SpriteAnimator::SpriteAnimator()
{
}

SpriteAnimator::~SpriteAnimator()
{
}

void SpriteAnimator::Awake()
{

}

void SpriteAnimator::Start()
{

}

void SpriteAnimator::SetColor(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
{
	_color = sf::Color(r, g, b, a);
	_sprite.setColor(_color);
}

void SpriteAnimator::SetPosition(float x, float y)
{
	_sprite.setPosition(sf::Vector2f(x, y));
}

void SpriteAnimator::SetRotation(float angle)
{
	_sprite.setRotation(angle);
}

void SpriteAnimator::SetScale(float x, float y)
{
	_sprite.scale(sf::Vector2f(x, y));
}

void SpriteAnimator::SetOrigin(float x, float y)
{
	_sprite.setOrigin(sf::Vector2f(x, y));
}

void SpriteAnimator::Update(float deltaTime)
{
	_currentAnimTime += deltaTime;

	if (_currentAnimTime >= _animRate)
	{
		_currentAnimTime = 0;
		_sprite.setTexture(_allTexture[_currentFrame]);
		_currentFrame++;
		if (_currentFrame >= _nbFrame)
			_currentFrame = 0;
	}

	float x = _parent->transform.position.x;
	float y = _parent->transform.position.y;
	SetPosition(x, y);
	float r = _parent->transform.rotation.z;
	SetRotation(r);
	float sx = _parent->transform.scale.x;
	float sy = _parent->transform.scale.y;
	SetScale(sx, sy);
}

void SpriteAnimator::Render(sf::RenderWindow* window)
{
	if(_nbFrame > 0)
		window->draw(_sprite);
}

void SpriteAnimator::Exit()
{

}

void SpriteAnimator::AddTexture(std::string fileName)
{
	_allTexture.push_back(ResourcesManager::Instance().GetTexture(fileName));
	if (_nbFrame == 0)
	{
		_sprite.setTexture(_allTexture[0]);
	}
	_nbFrame++;
}