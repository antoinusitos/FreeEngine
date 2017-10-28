#pragma once

#include <SFML/Audio.hpp>

#include <memory>
#include <mutex>
#include <iostream>

class GlobalListener
{
public:
	GlobalListener();
	~GlobalListener();

	// Get a unique instance of the time
	static GlobalListener& GlobalListener::Instance()
	{
		std::call_once(GlobalListener::onceFlag, []() {
			_instance.reset(new GlobalListener);
			//std::cout << "Getting  Window instance" << '\n';
		});

		return *(_instance.get());
	}

	void SetPosition(float x, float y);

	void SetGlobalVolume(float volume);

//Variables
private:
	// Unique instance of the time
	static std::unique_ptr<GlobalListener> _instance;
	static std::once_flag onceFlag;

	sf::Listener _listener;
};
