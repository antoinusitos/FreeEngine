#pragma once

#include <memory>
#include <mutex>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class ResourcesManager
{
public:
	ResourcesManager();
	~ResourcesManager();

	// Get a unique instance
	static ResourcesManager& ResourcesManager::Instance()
	{
		std::call_once(ResourcesManager::onceFlag, []() {
			_instance.reset(new ResourcesManager);
			//std::cout << "Getting  Resources Manager instance" << '\n';
		});

		return *(_instance.get());
	}

	/*const */sf::Font GetFont(const std::string fileName);
	const sf::SoundBuffer GetBuffer(const std::string fileName);
	const sf::Texture GetTexture(const std::string fileName);
	const void GetMusic(sf::Music& music, const std::string fileName);


//Variables
private:
	// Unique instance of the time
	static std::unique_ptr<ResourcesManager> _instance;
	static std::once_flag onceFlag;

	std::string _projectPath = "";
	std::string _resourcesPath = "";
};

