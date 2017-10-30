#include "CameraManager.h"
#include <iostream>
#include "Window.h"

std::unique_ptr<CameraManager> CameraManager::_instance;
std::once_flag CameraManager::onceFlag;

CameraManager::CameraManager()
{
	
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

void CameraManager::Init()
{
	int x = Window::Instance().GetScreenResolutionX();
	int y = Window::Instance().GetScreenResolutionY();
	_mainView.reset(sf::FloatRect(0, 0, x, y));
	_currentView = _mainView;
}

void CameraManager::ResizeCurrentView(int x, int y)
{
	_currentView.reset(sf::FloatRect(0, 0, x, y));
}