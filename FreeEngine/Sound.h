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

	void InitSound(std::string soundName);
	void InitMusic(std::string soundName);
	void Play();
	void Pause();
	void Stop();
	void SetOffset(int second);
	void SetPitch(float value);
	void SetLoop(bool mustLoop);

	//-----3D-----//
	void SetPosition(float x, float y);
	//Note from sfml
	//Cela peut �tre utile pour les sons �mis par l'�couteur lui-m�me (comme un bruit de tir, ou de pas). 
	//Cela a �galement comme effet int�ressant de d�sactiver la spatialisation si vous mettez la position de la source audio � (0, 0, 0).
	//Les sons non-spatialis�s peuvent se r�v�ler utiles dans de nombreuses situations : sons d'interface graphique (clics), musiques ambiantes, etc.
	void SetRelativeToListener(bool newState);
	void SetDistance(float minDist, float maxDist);

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

