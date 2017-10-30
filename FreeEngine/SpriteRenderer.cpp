#include "SpriteRenderer.h"
#include "ResourcesManager.h"

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
	_sprite.setScale(sf::Vector2f(x, y));
}

void SpriteRenderer::SetOrigin(float x, float y)
{
	_sprite.setOrigin(sf::Vector2f(x, y));
}