#include "UIManager.h"
#include "Composite.h"
#include "CameraManager.h"

std::unique_ptr<UIManager> UIManager::_instance;
std::once_flag UIManager::onceFlag;

UIManager::UIManager()
{
}

UIManager::~UIManager()
{
}

void UIManager::Update(const float deltaTime)
{
	_position.x = CameraManager::Instance().GetCurrentX();
	_position.y = CameraManager::Instance().GetCurrentY();

	for (std::vector<Composite*>::iterator it = _allComposite.begin(); it != _allComposite.end(); it++)
	{
		(*it)->Update(deltaTime);
	}
}

void UIManager::Render(sf::RenderWindow* window)
{
	for (std::vector<Composite*>::iterator it = _allComposite.begin(); it != _allComposite.end(); it++)
	{
		(*it)->Render(window);
	}
}