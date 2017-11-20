#include "SpriteAnimator.h"
#include "ResourcesManager.h"
#include "Composite.h"
#include "Debug.h"

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

void SpriteAnimator::SetColor(const unsigned int r, const unsigned int g, const unsigned int b, const unsigned int a)
{
	_color = sf::Color(r, g, b, a);
	_sprite.setColor(_color);
}

void SpriteAnimator::SetPosition(const float x, const float y)
{
	_sprite.setPosition(sf::Vector2f(x, y));
}

void SpriteAnimator::SetRotation(const float angle)
{
	_sprite.setRotation(angle);
}

void SpriteAnimator::SetScale(const float x, const float y)
{
	_sprite.scale(sf::Vector2f(x, y));
}

void SpriteAnimator::SetOrigin(const float x, const float y)
{
	_sprite.setOrigin(sf::Vector2f(x, y));
}

void SpriteAnimator::Update(const float deltaTime)
{
	_currentAnimTime += deltaTime * _animationSpeed;

	if (_currentAnimTime >= _animRate)
	{
		_currentAnimTime = 0;

		if (!_isAtlas)
		{
			if ((int)_allTexture.size() != 0)
				_sprite.setTexture(_allTexture[_currentFrame]);
			else
				Debug::Instance().Print("No texture to render on this sprite animator", DebugMessageType::DEBUGERROR);
		}
		else
		{
			if ((int)_atlasRect.size() != 0)
			{
				_sprite.setTexture(_allTexture[0]);
				_sprite.setTextureRect(_atlasRect[_currentFrame]);

			}
			else
				Debug::Instance().Print("No texture from atlas to render on this sprite animator", DebugMessageType::DEBUGERROR);
		}
		_currentFrame++;
		if (_currentFrame >= _nbFrame)
			_currentFrame = 0;
	}

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

void SpriteAnimator::Render(sf::RenderWindow* window)
{
	if(_nbFrame > 0)
		window->draw(_sprite);
}

void SpriteAnimator::Exit()
{

}

void SpriteAnimator::AddTexture(const std::string fileName)
{
	_allTexture.push_back(ResourcesManager::Instance().GetTexture(fileName));
	if (_nbFrame == 0)
	{
		_sprite.setTexture(_allTexture[0]);
	}
	_nbFrame++;
}

void SpriteAnimator::SetAnimationSpeed(const float newSpeed)
{
	_animationSpeed = newSpeed;
}

void SpriteAnimator::AddAtlas(const std::string fileName, int nbFrames, int totalHeight, int totalWidth, int frameHeight, int frameWidth, int offsetX, int offsetY)
{
	_isAtlas = true;
	_nbFrame = nbFrames;

	_allTexture.push_back(ResourcesManager::Instance().GetTexture(fileName));

	if (totalHeight % frameHeight != 0)
		Debug::Instance().Print(fileName + " has a ratio totalHeight / frameHeight with floating number", DebugMessageType::DEBUGWARNING);

	if (totalWidth % frameWidth != 0)
		Debug::Instance().Print(fileName + " has a ratio totalWidth / frameWidth with floating number", DebugMessageType::DEBUGWARNING);

	int tempHeight = offsetY;
	int tempWidth = offsetX;

	for (int i = 0; i < nbFrames; i++)
	{
		_atlasRect.push_back(sf::IntRect(tempWidth, tempHeight, frameWidth, frameHeight));
		tempWidth += frameWidth;
		if (tempWidth > totalWidth)
		{
			tempWidth = 0;
			tempHeight += frameHeight;
		}
	}

	Debug::Instance().Log("Atlas created !", DebugMessageType::DEBUGENGINE);
}