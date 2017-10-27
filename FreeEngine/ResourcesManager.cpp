#include "ResourcesManager.h"
#include "DebugWindowLayout.h"
#include "Data.h"
#include "Debug.h"

std::unique_ptr<ResourcesManager> ResourcesManager::_instance;
std::once_flag ResourcesManager::onceFlag;

ResourcesManager::ResourcesManager()
{
	_projectPath = Data::Instance().GetProjetPath();
	_resourcesPath = _projectPath + "FreeEngine/Assets/Resources/";
}

ResourcesManager::~ResourcesManager()
{
}

sf::Font ResourcesManager::GetFont(std::string fontName)
{
	sf::Font toReturn;
	if (!toReturn.loadFromFile(_resourcesPath + fontName))
	{
		Debug::Instance().Print("Error : fail to load font " + _resourcesPath + fontName + '\n', DebugMessageType::ERROR);
	}
	return toReturn;
}

sf::SoundBuffer ResourcesManager::GetBuffer(std::string fileName)
{
	sf::SoundBuffer toReturn;
	if (!toReturn.loadFromFile(_resourcesPath + fileName))
	{
		Debug::Instance().Print("Error : fail to load sound " + _resourcesPath + fileName + '\n', DebugMessageType::ERROR);
	}
	return toReturn;
}