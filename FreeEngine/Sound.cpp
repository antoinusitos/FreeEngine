#include "Sound.h"
#include "Transform.h"
#include "ResourcesManager.h"

Sound::Sound()
{
	_transform = Transform();
}

Sound::~Sound()
{
}

void Sound::Init(std::string soundName)
{
	_buffer = ResourcesManager::Instance().GetBuffer(soundName);
	_sound = sf::Sound();
	_sound.setBuffer(_buffer);
}

void Sound::Play()
{
	_sound.play();
}

void Sound::Pause()
{
	_sound.pause();
}

void Sound::Stop()
{
	_sound.stop();
}

void Sound::SetOffset(int second)
{
	_sound.setPlayingOffset(sf::seconds(second));
}

void Sound::SetPosition(float x, float y)
{
	_transform.position.x = x;
	_transform.position.y = y;
}