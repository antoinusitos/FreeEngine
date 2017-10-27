#pragma once

#include <SFML/Audio.hpp>
#include <string>

class Transform;

class Sound
{
public:
	Sound();
	~Sound();

	void Init(std::string soundName);
	void Play();
	void Pause();
	void Stop();
	void SetOffset(int second);
	void SetPosition(float x, float y);

private:
	sf::SoundBuffer _buffer;
	sf::Sound _sound;
	sf::Music _music;

	bool _isMusic = false;

	float _pitch = 1.f;
	float _volume = 100.f;
	bool _loop = false;

	Transform _transform;
};

