#include "UIManager.h"
#include "GameObject.h"
#include "CameraManager.h"
#include "UITransform.h"

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
	_position.x = CameraManager::Instance().GetCurrentX(); // center
	_position.y = CameraManager::Instance().GetCurrentY(); // center

	for (std::vector<GameObject*>::iterator it = _allComponents.begin(); it != _allComponents.end(); it++)
	{
		for (std::vector<Leaf*>::iterator comp = (*it)->components.begin(); comp != (*it)->components.end(); ++comp)
		{
			UITransform* ui = static_cast<UITransform*>(*comp);
			if (ui != NULL)
			{
				(*it)->transform.position = _position + ui->offset;
				break;
			}
		}
		(*it)->Update(deltaTime);
	}
}

void UIManager::Render(sf::RenderWindow* window)
{
	for (std::vector<GameObject*>::iterator it = _allComponents.begin(); it != _allComponents.end(); it++)
	{
		(*it)->Render(window);
	}
}

void UIManager::AddGameObjectToList(GameObject* newGo)
{
	_allComponents.push_back(newGo);
}

void UIManager::EmptyGameObjectList()
{
	for (std::vector<GameObject*>::iterator it = _allComponents.begin(); it != _allComponents.end(); ++it)
	{
		delete (*it);
	}
	_allComponents.clear();
}