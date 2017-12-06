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

void SceneManager::LoadScene(const std::string name, bool InitScene)
{
	for (std::vector<SceneInfo*>::iterator it = _allScene.begin(); it != _allScene.end(); it++)
	{
		if (name == (*it)->name)
		{
			std::cout << "Scene " << name << " found ! Loading..." << '\n';

			if (_currentScene != nullptr)
			{
				//TODO : fix transition and remove of sprite renderer from test scene to menu
				_currentScene->Destroy();
			}

			_currentScene = (*it)->scene;
			
			Debug::Instance().Print("Current Scene : " + _currentScene->name, DebugMessageType::DEBUGENGINE);
			
			if (InitScene)
			{
				_currentScene->LoadObject();
				_currentScene->PreAwake();
				_currentScene->Awake();
				_currentScene->Start();
			}
			return;
		}
	}
	Debug::Instance().Print("Cannot load scene : " + name, DebugMessageType::DEBUGERROR);
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

			SceneInfo* si = new SceneInfo();
			si->name = token;
			si->scene = new Scene(token);

			_allScene.push_back(si);

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
	for (std::vector<SceneInfo*>::iterator it = _allScene.begin(); it != _allScene.end(); it++)
	{
		toWrite += (*it)->name + '\n';
	}
	FileHandler::Instance().WriteFile(_fileName, toWrite);

	for (std::vector<SceneInfo*>::iterator it = _allScene.begin(); it != _allScene.end(); it++)
	{
		(*it)->scene->SaveObject();
	}
}

void SceneManager::ToStringAllScenes()
{
	std::cout << "all scenes:" << '\n';

	for (std::vector<SceneInfo*>::iterator it = _allScene.begin(); it != _allScene.end(); it++)
	{
		std::cout << (*it)->name << '\n';
	}
}

void SceneManager::NewScene(const std::string name)
{
	for (std::vector<SceneInfo*>::iterator it = _allScene.begin(); it != _allScene.end(); it++)
	{
		if (name == (*it)->name)
		{
			Debug::Instance().Print("A scene with this name already exist !", DebugMessageType::DEBUGERROR);
			return;
		}
	}

	Scene* tmpScene = new Scene(name);
	SceneInfo* si = new SceneInfo();
	si->name = name;
	si->scene = tmpScene;
	_allScene.push_back(si);
}

void SceneManager::NewScene(Scene* newScene)
{
	SceneInfo* si = new SceneInfo();
	si->name = newScene->name;
	si->scene = newScene;
	_allScene.push_back(si);
}

Scene* SceneManager::GetCurrentScene()
{
	return _currentScene;
}

void SceneManager::PreAwakeCurrentScene()
{
	if (_currentScene != nullptr)
	{
		Debug::Instance().Print("Current Scene : " + _currentScene->name, DebugMessageType::DEBUGENGINE);
		_currentScene->PreAwake();
	}
}

void SceneManager::AwakeCurrentScene()
{
	if (_currentScene != nullptr)
	{
		_currentScene->Awake();
	}
}

void SceneManager::StartCurrentScene()
{
	if (_currentScene != nullptr)
	{
		_currentScene->Start();
	}
}

void SceneManager::UpdateCurrentScene(float deltaTime)
{
	if (_currentScene != nullptr)
	{
		_currentScene->Update(deltaTime);
	}
}

void SceneManager::RenderCurrentScene(sf::RenderWindow* window)
{
	if (_currentScene != nullptr)
	{
		_currentScene->Render(window);
	}
}