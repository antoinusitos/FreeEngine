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
		});

		return *(_instance.get());
	}

	void SetPosition(const float x, const float y);

	void SetGlobalVolume(const float volume);

//Variables
private:
	// Unique instance of the time
	static std::unique_ptr<GlobalListener> _instance;
	static std::once_flag onceFlag;

	sf::Listener _listener;
};

