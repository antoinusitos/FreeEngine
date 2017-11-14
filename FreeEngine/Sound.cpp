#include "Sound.h"
#include "ResourcesManager.h"

Sound::Sound()
{
	_transform = Transform();
}

Sound::~Sound()
{
}

void Sound::InitSound(std::string soundName)
{
	_buffer = ResourcesManager::Instance().GetBuffer(soundName);
	_sound = sf::Sound();
	_sound.setBuffer(_buffer);
	_type = SoundType::SOUND;
}

void Sound::InitMusic(std::string soundName)
{
	 ResourcesManager::Instance().GetMusic(_music, soundName);
	 _type = SoundType::MUSIC;
}

const void Sound::Play()
{
	if (_type == SoundType::MUSIC)
		_music.play();
	else if (_type == SoundType::SOUND)
		_sound.play();
}

const void Sound::Pause()
{
	if (_type == SoundType::MUSIC)
		_music.pause();
	else if (_type == SoundType::SOUND)
		_sound.pause();
}

const void Sound::Stop()
{
	if (_type == SoundType::MUSIC)
		_music.stop();
	else if (_type == SoundType::SOUND)
		_sound.stop();
}

void Sound::SetOffset(const float second)
{
	if (_type == SoundType::MUSIC)
		_music.setPlayingOffset(sf::seconds(second));
	else if (_type == SoundType::SOUND)
		_sound.setPlayingOffset(sf::seconds(second));
}

void Sound::SetPitch(const float value)
{
	_sound.setPitch(value);
}

void Sound::SetLoop(const bool mustLoop)
{
	if (_type == SoundType::MUSIC)
		_music.setLoop(mustLoop);
	else if (_type == SoundType::SOUND)
		_sound.setLoop(mustLoop);
}

void Sound::SetPosition(const float x, const float y, const float z)
{
	_transform.position.x = x;
	_transform.position.y = y;
	_transform.position.z = z;
	_sound.setPosition(x, y, z);
}

void Sound::SetRelativeToListener(const bool newState)
{
	_sound.setRelativeToListener(newState);
}

void Sound::SetDistance(const float minDist, const float maxDist)
{
	_sound.setMinDistance(minDist);
	_sound.setAttenuation(maxDist);
}