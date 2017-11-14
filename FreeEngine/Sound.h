#pragma once

#include <SFML/Audio.hpp>
#include <string>
#include "Transform.h"
#include "Data.h"

class Sound
{
public:
	Sound();
	~Sound();

	void InitSound(const std::string soundName);
	void InitMusic(const std::string soundName);
	const void Play();
	const void Pause();
	const void Stop();
	void SetOffset(const float second);
	void SetPitch(const float value);
	void SetLoop(const bool mustLoop);

	//-----3D-----//
	
	//BECAREFUL, X is FORWARD, Z is RIGHT
	void SetPosition(const float x, const float y, const float z);
	//Note from sfml
	//Cela peut être utile pour les sons émis par l'écouteur lui-même (comme un bruit de tir, ou de pas). 
	//Cela a également comme effet intéressant de désactiver la spatialisation si vous mettez la position de la source audio à (0, 0, 0).
	//Les sons non-spatialisés peuvent se révéler utiles dans de nombreuses situations : sons d'interface graphique (clics), musiques ambiantes, etc.
	void SetRelativeToListener(const bool newState);
	void SetDistance(const float minDist, const float maxDist);

private:
	sf::SoundBuffer _buffer;
	sf::Sound _sound;
	sf::Music _music;

	SoundType _type;

	float _pitch = 1.f;
	float _volume = 100.f;
	bool _loop = false;

	Transform _transform;
};

