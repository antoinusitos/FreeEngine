#include "SceneManager.h"
#include "FileHandler.h"
#include "Debug.h"
#include "Scene.h"

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
	for (std::vector<std::string>::iterator it = _allSceneName.begin(); it != _allSceneName.end(); it++)
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
	_allSceneName.push_back(name);
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

			_allSceneName.push_back(token);

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
	for (std::vector<std::string>::iterator it = _allSceneName.begin(); it != _allSceneName.end(); it++)
	{
		toWrite += (*it) + '\n';
	}
	FileHandler::Instance().WriteFile(_fileName, toWrite);

	for (std::vector<Scene*>::iterator it = _allScene.begin(); it != _allScene.end(); it++)
	{
		(*it)->SaveObject();
	}
}

void SceneManager::ToStringAllScenes()
{
	std::cout << "all scenes:" << '\n';

	for (std::vector<std::string>::iterator it = _allSceneName.begin(); it != _allSceneName.end(); it++)
	{
		std::cout << (*it) << '\n';
	}
}

void SceneManager::NewScene(const std::string name)
{
	for (std::vector<std::string>::iterator it = _allSceneName.begin(); it != _allSceneName.end(); it++)
	{
		if (name == (*it))
		{
			Debug::Instance().Print("A scene with this name already exist !", DebugMessageType::DEBUGERROR);
			return;
		}
	}

	_currentScene = new Scene(name);
	_allSceneName.push_back(name);
	_allScene.push_back(_currentScene);
	Debug::Instance().Log("Set Current Scene to " + name, DebugMessageType::DEBUGENGINE);
}

Scene* SceneManager::GetCurrentScene()
{
	return _currentScene;
}