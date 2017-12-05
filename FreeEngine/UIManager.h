#pragma once

#include <memory>
#include <mutex>
#include <vector>
#include <SFML\Graphics.hpp>
#include "FVector3.h"

class GameObject;

class UIManager
{
public:
	UIManager();
	~UIManager();

	// Get a unique instance of the time
	static UIManager& UIManager::Instance()
	{
		std::call_once(UIManager::onceFlag, []() {
			_instance.reset(new UIManager);
			//std::cout << "Getting UIManager instance" << '\n';
		});

		return *(_instance.get());
	}

	void Update(const float deltaTime);
	void Render(sf::RenderWindow* window);

	void AddGameObjectToList(GameObject* newGo);

private:
	// Unique instance of the time
	static std::unique_ptr<UIManager> _instance;
	static std::once_flag onceFlag;

	std::vector<GameObject*> _allComponents;

	FVector3 _position = FVector3();
};

