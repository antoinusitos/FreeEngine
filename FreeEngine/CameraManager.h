#pragma once

#include "SFML/Graphics.hpp"
#include <memory>
#include <mutex>

class CameraManager
{
public:
	CameraManager();
	~CameraManager();

	// Get a unique instance of the time
	static CameraManager& CameraManager::Instance()
	{
		std::call_once(CameraManager::onceFlag, []() {
			_instance.reset(new CameraManager);
			//std::cout << "Getting  Window instance" << '\n';
		});

		return *(_instance.get());
	}

	void Move(int x, int y);

	sf::View GetView();

private:
	// Unique instance of the time
	static std::unique_ptr<CameraManager> _instance;
	static std::once_flag onceFlag;

	sf::View _mainView;
};

