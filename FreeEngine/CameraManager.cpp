#include "CameraManager.h"
#include <iostream>
#include "Window.h"
#include "GameObject.h"

std::unique_ptr<CameraManager> CameraManager::_instance;
std::once_flag CameraManager::onceFlag;

CameraManager::CameraManager()
{
	
}

CameraManager::~CameraManager()
{
}

void CameraManager::Move(const float x, const float y)
{
	_currentX = x;
	_currentY = y;
	_mainView.move(x, y);
}

const sf::View CameraManager::GetView()
{
	return _mainView;
}

void CameraManager::Init()
{
	float x = Window::Instance().GetScreenResolutionX();
	float y = Window::Instance().GetScreenResolutionY();
	_mainView.reset(sf::FloatRect(0, 0, x, y));
	_currentX = 0;
	_currentY = 0;
	_currentView = _mainView;
}

void CameraManager::ResizeCurrentView(const float x, const float y)
{
	_currentView.reset(sf::FloatRect(0, 0, x, y));
}

const float CameraManager::GetCurrentX()
{
	return _currentX;
}

const float CameraManager::GetCurrentY()
{
	return _currentY;
}