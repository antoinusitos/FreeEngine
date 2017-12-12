#include "SpriteRenderer.h"
#include "ResourcesManager.h"
#include "Composite.h"

SpriteRenderer::SpriteRenderer()
{
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::Init(const std::string path)
{
	_texture = ResourcesManager::Instance().GetTexture(path);
	_sprite.setTexture(_texture);
	init = true;
}

const sf::Sprite SpriteRenderer::GetSprite()
{
	return _sprite;
}

const sf::Texture SpriteRenderer::GetTexture()
{
	return _texture;
}

void SpriteRenderer::SetSmooth(const bool newState)
{
	_smooth = newState;
	_texture.setSmooth(_smooth);
}

void SpriteRenderer::SetRepeat(const bool newState)
{
	_repeat = newState;
	_texture.setRepeated(_repeat);
}

void SpriteRenderer::SetColor(const unsigned int r, const unsigned int g, const unsigned int b, const unsigned int a)
{
	_color = sf::Color(r, g, b, a);
	_sprite.setColor(_color);
}

void SpriteRenderer::SetPosition(const float x, const float y)
{
	_sprite.setPosition(sf::Vector2f(x, y));
}

void SpriteRenderer::SetRotation(const float angle)
{
	_sprite.setRotation(angle);
}

void SpriteRenderer::SetScale(const float x, const float y)
{
	_sprite.setScale(sf::Vector2f(x, y));
}

void SpriteRenderer::SetOrigin(const float x, const float y)
{
	_sprite.setOrigin(sf::Vector2f(x, y));
}

void SpriteRenderer::Awake()
{

}

void SpriteRenderer::Start()
{

}

void SpriteRenderer::Update(const float deltaTime)
{
	if (_parent != nullptr)
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
}

void SpriteRenderer::Render(sf::RenderWindow* window)
{
	if (init)
	{
		Window::Instance().DrawObject(_sprite);
		//window->draw(_sprite);
	}
}

void SpriteRenderer::Exit()
{

}