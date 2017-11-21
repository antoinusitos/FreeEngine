#pragma once

#include "SFML/Graphics.hpp"
#include <memory>
#include <mutex>

class GameObject;

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

	void Move(const float x, const float y);

	const sf::View GetView();

	void Init();

	void ResizeCurrentView(const float x, const float y);

	const float GetCurrentX();
	const float GetCurrentY();

	void Render(sf::RenderWindow* SFMLWindow);
	void Update(const float deltaTime);

	void SetFade(const float fadeValue);

private:
	// Unique instance of the time
	static std::unique_ptr<CameraManager> _instance;
	static std::once_flag onceFlag;

	sf::View _mainView;
	sf::View _currentView;
	sf::View _debugView;

	float _currentX;
	float _currentY;

	float _debugViewX;
	float _debugViewY;
	float _debugViewSpeed = 100.0f;

	sf::RectangleShape _fadeRect;
	sf::Color _fadeColor;

	sf::Font* _font;

	sf::Text _titleText;
	sf::Text _camSpeed;

	bool _editing = false;
};