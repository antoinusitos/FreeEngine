#include "SceneManager.h"
#include "FileHandler.h"
#include "Debug.h"

std::unique_ptr<SceneManager> SceneManager::_instance;
std::once_flag SceneManager::onceFlag;

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::LoadScene(const std::string name)
{
	for (std::vector<std::string>::iterator it = _allScene.begin(); it != _allScene.end(); it++)
	{
		if (name == (*it))
		{
			std::cout << "Scene " << name << " found !" << '\n';
			//TODO : Load the scene from the right file
		}
	}
}

void SceneManager::SaveScene(const std::string name)
{
	_allScene.push_back(name);
}

void SceneManager::LoadScenesFromFile()
{
	bool fileReadable = false;
	std::string allFiles = FileHandler::Instance().ReadFile(_fileName, &fileReadable);
	if (fileReadable)
	{
		std::string delimiter = "\n";

		size_t pos = 0;
		std::string token;
		while ((pos = allFiles.find(delimiter)) != std::string::npos)
		{
			token = allFiles.substr(0, pos);

			_allScene.push_back(token);

			allFiles.erase(0, pos + delimiter.length());
		}

		ToStringAllScenes();
	}
	else
	{
		Debug::Instance().Print("File "+ _fileName +" not readable", DebugMessageType::DEBUGERROR);
	}
}

void SceneManager::SaveScenesInFile()
{
	std::string toWrite = "";
	for (std::vector<std::string>::iterator it = _allScene.begin(); it != _allScene.end(); it++)
	{
		toWrite += (*it) + '\n';
	}
	FileHandler::Instance().WriteFile(_fileName, toWrite);
}

void SceneManager::ToStringAllScenes()
{
	std::cout << "all scenes:" << '\n';

	for (std::vector<std::string>::iterator it = _allScene.begin(); it != _allScene.end(); it++)
	{
		std::cout << (*it) << '\n';
	}
}