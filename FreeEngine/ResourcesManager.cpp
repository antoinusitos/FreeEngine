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

/*const*/ sf::Font ResourcesManager::GetFont(const std::string fontName)
{
	sf::Font toReturn;
	if (!toReturn.loadFromFile(_resourcesPath + fontName))
	{
		Debug::Instance().Print("Error : fail to load font " + _resourcesPath + fontName + '\n', DebugMessageType::DEBUGERROR);
	}
	return toReturn;
}

const sf::SoundBuffer ResourcesManager::GetBuffer(const std::string fileName)
{
	sf::SoundBuffer toReturn;
	if (!toReturn.loadFromFile(_resourcesPath + fileName))
	{
		Debug::Instance().Print("Error : fail to load sound " + _resourcesPath + fileName + '\n', DebugMessageType::DEBUGERROR);
	}
	return toReturn;
}

const void ResourcesManager::GetMusic(sf::Music& music, const std::string fileName)
{
	if (!music.openFromFile(_resourcesPath + fileName))
	{
		Debug::Instance().Print("Error : fail to load sound " + _resourcesPath + fileName + '\n', DebugMessageType::DEBUGERROR);
	}
}


const sf::Texture ResourcesManager::GetTexture(const std::string fileName)
{
	sf::Texture toReturn;
	if (!toReturn.loadFromFile(_resourcesPath + fileName))
	{
		Debug::Instance().Print("Error : fail to load texture " + _resourcesPath + fileName + '\n', DebugMessageType::DEBUGERROR);
	}
	return toReturn;
}

const void ResourcesManager::GetVertexShader(sf::Shader& shader, const std::string fileName)
{
	if (!shader.loadFromFile(_resourcesPath + fileName, sf::Shader::Vertex))
	{
		Debug::Instance().Print("Error : fail to load vertex shader " + _resourcesPath + fileName + '\n', DebugMessageType::DEBUGERROR);
	}
}

const void ResourcesManager::GetFragmentShader(sf::Shader& shader, const std::string fileName)
{
	if (!shader.loadFromFile(_resourcesPath + fileName, sf::Shader::Fragment))
	{
		Debug::Instance().Print("Error : fail to load fragment shader " + _resourcesPath + fileName + '\n', DebugMessageType::DEBUGERROR);
	}
}

const void ResourcesManager::GetVertexFragmentShader(sf::Shader& shader, const std::string vertexFileName, const std::string fragmentFileName)
{
	if (!shader.loadFromFile(_resourcesPath + vertexFileName, _resourcesPath + fragmentFileName))
	{
		Debug::Instance().Print("Error : fail to load vertex shader " + _resourcesPath + vertexFileName + " or fragment shader " + _resourcesPath + fragmentFileName + '\n', DebugMessageType::DEBUGERROR);
	}
}

const sf::Image ResourcesManager::GetImage(const std::string fileName)
{
	sf::Image toReturn;
	if (!toReturn.loadFromFile(_resourcesPath + fileName))
	{
		Debug::Instance().Print("Error : fail to load image " + _resourcesPath + fileName + '\n', DebugMessageType::DEBUGERROR);
	}
	return toReturn;
}