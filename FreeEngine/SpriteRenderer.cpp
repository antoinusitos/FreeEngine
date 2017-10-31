#include "SpriteRenderer.h"
#include "ResourcesManager.h"
#include "Composite.h"

SpriteRenderer::SpriteRenderer()
{
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::Init(std::string path)
{
	_texture = ResourcesManager::Instance().GetTexture(path);
	_sprite.setTexture(_texture);
	init = true;
}

sf::Sprite SpriteRenderer::GetSprite()
{
	return _sprite;
}

sf::Texture SpriteRenderer::GetTexture()
{
	return _texture;
}

void SpriteRenderer::SetSmooth(bool newState)
{
	_smooth = newState;
	_texture.setSmooth(_smooth);
}

void SpriteRenderer::SetRepeat(bool newState)
{
	_repeat = newState;
	_texture.setRepeated(_repeat);
}

void SpriteRenderer::SetColor(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
{
	_color = sf::Color(r, g, b, a);
	_sprite.setColor(_color);
}

void SpriteRenderer::SetPosition(float x, float y)
{
	_sprite.setPosition(sf::Vector2f(x, y));
}

void SpriteRenderer::SetRotation(float angle)
{
	_sprite.setRotation(angle);
}

void SpriteRenderer::SetScale(float x, float y)
{
	_sprite.scale(sf::Vector2f(x, y));
}

void SpriteRenderer::SetOrigin(float x, float y)
{
	_sprite.setOrigin(sf::Vector2f(x, y));
}

void SpriteRenderer::Awake()
{

}

void SpriteRenderer::Start()
{

}

void SpriteRenderer::Update(float deltaTime)
{
	float x = _parent->transform.position.x;
	float y = _parent->transform.position.y;
	SetPosition(x, y);
	float r = _parent->transform.rotation.z;
	SetRotation(r);
	float sx = _parent->transform.scale.x;
	float sy = _parent->transform.scale.y;
	SetScale(sx, sy);
}

void SpriteRenderer::Render(sf::RenderWindow* window)
{
	if (init)
	{
		window->draw(_sprite);
	}
}

void SpriteRenderer::Exit()
{

}