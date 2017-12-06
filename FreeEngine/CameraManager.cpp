#include "CameraManager.h"
#include <iostream>
#include "Window.h"
#include "GameObject.h"
#include "FMath.h"
#include "EditorManager.h"
#include "Input.h"
#include "ResourcesManager.h"

std::unique_ptr<CameraManager> CameraManager::_instance;
std::once_flag CameraManager::onceFlag;

CameraManager::CameraManager()
{
	_font = new sf::Font(ResourcesManager::Instance().GetFont("arial.ttf"));
}

CameraManager::~CameraManager()
{

}

void CameraManager::Move(const float x, const float y)
{
	_currentView.move(x - _currentX, y - _currentY);
	_currentX = x;
	_currentY = y;
	Window::Instance().SetView(_currentView);
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
	_mainView.setCenter(x/ 2, y/2);
	_currentX = x / 2;
	_currentY = y / 2;
	_currentView = _mainView;

	_fadeRect = sf::RectangleShape(sf::Vector2f(0, 0));
	_fadeRect.setSize(sf::Vector2f(x, y));
	_fadeColor = sf::Color(0, 0, 0, 255);
	_fadeRect.setFillColor(_fadeColor);

	_titleText.setFont(*_font);
	_titleText.setString("EDIT MODE");
	_titleText.setCharacterSize(24);

	_camSpeed.setFont(*_font);
	std::string s = "Cam Speed = " + std::to_string(static_cast<int>(_debugViewSpeed));
	_camSpeed.setString(s);
	_camSpeed.setCharacterSize(24);

	_camPos.setFont(*_font);
	_camPos.setCharacterSize(24);

	_debugCamPos.setFont(*_font);
	_debugCamPos.setCharacterSize(24);
}

void CameraManager::ResizeCurrentView(const float x, const float y)
{
	_currentView.reset(sf::FloatRect(0, 0, x, y));
}

const float CameraManager::GetCurrentX()
{
	return _currentX + _localOffset.x;
}

const float CameraManager::GetCurrentY()
{
	return _currentY + _localOffset.y;
}

void CameraManager::Render(sf::RenderWindow* SFMLWindow)
{
	if (_editing)
	{
		_titleText.setPosition(
			_debugViewX - (Window::Instance().GetScreenResolutionX() / 2) + 10,
			_debugViewY - (Window::Instance().GetScreenResolutionY() / 2) + (10 + _titleText.getCharacterSize())
		);
		_camSpeed.setPosition(
			_debugViewX - (Window::Instance().GetScreenResolutionX() / 2) + 10,
			_debugViewY - (Window::Instance().GetScreenResolutionY() / 2) + (10 + _titleText.getCharacterSize()) * 2
		);
		_camPos.setPosition(
			_debugViewX - (Window::Instance().GetScreenResolutionX() / 2) + 10,
			_debugViewY - (Window::Instance().GetScreenResolutionY() / 2) + (10 + _titleText.getCharacterSize()) * 3
		);
		_debugCamPos.setPosition(
			_debugViewX - (Window::Instance().GetScreenResolutionX() / 2) + 10,
			_debugViewY - (Window::Instance().GetScreenResolutionY() / 2) + (10 + _titleText.getCharacterSize()) * 4
		);
		SFMLWindow->draw(_titleText);
		SFMLWindow->draw(_camSpeed);
		SFMLWindow->draw(_camPos);
		SFMLWindow->draw(_debugCamPos);
	}

	_fadeRect.setFillColor(_fadeColor);
	float x = Window::Instance().GetScreenResolutionX();
	float y = Window::Instance().GetScreenResolutionY();
	_fadeRect.setPosition(_currentX - x / 2, _currentY - y / 2);
	SFMLWindow->draw(_fadeRect);
}

void CameraManager::SetFade(const float fadeValue)
{
	_fadeColor.a = FMath::Clamp(fadeValue, 0, 255);
}

void CameraManager::Update(const float deltaTime)
{
	if (EditorManager::Instance().GetCurrentState() == EditorState::EDITING)
	{
		if (!_editing)
		{
			float x = Window::Instance().GetScreenResolutionX();
			float y = Window::Instance().GetScreenResolutionY();
			_debugViewX = _currentX;
			_debugViewY = _currentY;
			_debugView.reset(sf::FloatRect(_debugViewX - x / 2, _debugViewY - y / 2, x, y));
			Window::Instance().SetView(_debugView);
			_editing = true;
		}
	}
	else
	{
		if (_editing)
		{
			Window::Instance().SetView(_currentView);
			_editing = false;
		}
	}

	if (_editing)
	{
		float tempX = 0;
		if (Input::Instance().GetKeyPressed(KEYCODE::ARROWLEFT))
		{
			tempX -= deltaTime * _debugViewSpeed;
		}
		if (Input::Instance().GetKeyPressed(KEYCODE::ARROWRIGHT))
		{
			tempX += deltaTime * _debugViewSpeed;
		}

		float tempY = 0;
		if (Input::Instance().GetKeyPressed(KEYCODE::ARROWUP))
		{
			tempY -= deltaTime * _debugViewSpeed;
		}
		if (Input::Instance().GetKeyPressed(KEYCODE::ARROWDOWN))
		{
			tempY += deltaTime * _debugViewSpeed;
		}

		if (Input::Instance().GetKeyPressed(KEYCODE::A))
		{
			_debugViewSpeed -= deltaTime * 10;
		}
		else if (Input::Instance().GetKeyPressed(KEYCODE::Z))
		{
			_debugViewSpeed += deltaTime * 10;
		}

		_debugView.move(tempX, tempY);
		_debugViewX += tempX;
		_debugViewY += tempY;
		Window::Instance().SetView(_debugView);

		std::string s = "Cam Speed = " + std::to_string(static_cast<int>(_debugViewSpeed));
		_camSpeed.setString(s);
		std::string pos = "Cam Pos = (" + std::to_string(_currentX) + "," + std::to_string(_currentY) + "," + "0)";
		_camPos.setString(pos);
		std::string posDebug = "Debug Cam Pos = (" + std::to_string(_debugViewX)+ "," + std::to_string(_debugViewY) + "," + "0)";
		_debugCamPos.setString(posDebug);
	}
}

void CameraManager::SetLocalOffset(const FVector3& newOffset)
{
	_localOffset = newOffset;
}