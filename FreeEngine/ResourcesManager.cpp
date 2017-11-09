#include "ResourcesManager.h"
#include "DebugWindowLayout.h"
#include "Data.h"
#include "Debug.h"

std::unique_ptr<ResourcesManager> ResourcesManager::_instance;
std::once_flag ResourcesManager::onceFlag;

ResourcesManager::ResourcesManager()
{
	_projectPath = Data::Instance().GetProjetPath();
	if (ISRELEASE)
	{
		_resourcesPath = _projectPath + RELEASEFOLDER;
		Debug::Instance().Log("RELEASE VERSION " + RELEASEVERSION, DebugMessageType::DEBUGENGINE);
	}
	else
	{
		Debug::Instance().Log("DEBUG VERSION " + RELEASEVERSION, DebugMessageType::DEBUGENGINE);
		_resourcesPath = _projectPath + DEBUGFOLDER;
	}

	Debug::Instance().Log("Resources Path : " + _resourcesPath + '\n', DebugMessageType::DEBUGENGINE);

	_resourcesPath += "/Assets/Resources/";
}

ResourcesManager::~ResourcesManager()
{
}

sf::Font ResourcesManager::GetFont(std::string fontName)
{
	sf::Font toReturn;
	if (!toReturn.loadFromFile(_resourcesPath + fontName))
	{
		Debug::Instance().Print("Error : fail to load font " + _resourcesPath + fontName + '\n', DebugMessageType::DEBUGERROR);
	}
	return toReturn;
}

sf::SoundBuffer ResourcesManager::GetBuffer(std::string fileName)
{
	sf::SoundBuffer toReturn;
	if (!toReturn.loadFromFile(_resourcesPath + fileName))
	{
		Debug::Instance().Print("Error : fail to load sound " + _resourcesPath + fileName + '\n', DebugMessageType::DEBUGERROR);
	}
	return toReturn;
}

void ResourcesManager::GetMusic(sf::Music& music, std::string fileName)
{
	if (!music.openFromFile(_resourcesPath + fileName))
	{
		Debug::Instance().Print("Error : fail to load sound " + _resourcesPath + fileName + '\n', DebugMessageType::DEBUGERROR);
	}
}


sf::Texture ResourcesManager::GetTexture(std::string fileName)
{
	sf::Texture toReturn;
	if (!toReturn.loadFromFile(_resourcesPath + fileName))
	{
		Debug::Instance().Print("Error : fail to load texture " + _resourcesPath + fileName + '\n', DebugMessageType::DEBUGERROR);
	}
	return toReturn;
}