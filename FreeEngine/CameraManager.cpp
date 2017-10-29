#include "CameraManager.h"
#include <iostream>

std::unique_ptr<CameraManager> CameraManager::_instance;
std::once_flag CameraManager::onceFlag;

CameraManager::CameraManager()
{
	_mainView.reset(sf::FloatRect(200, 200, 300, 200));
	_mainView.setViewport(sf::FloatRect(0.25f, 0.25, 0.5f, 0.5f));
}

CameraManager::~CameraManager()
{
}

void CameraManager::Move(int x, int y)
{
	_mainView.move(x, y);
}

sf::View CameraManager::GetView()
{
	return _mainView;
}