#pragma once

#include <memory>
#include <mutex>
#include <vector>

class Scene;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	// Get a unique instance of the time
	static SceneManager& SceneManager::Instance()
	{
		std::call_once(SceneManager::onceFlag, []() {
			_instance.reset(new SceneManager);
		});

		return *(_instance.get());
	}

	void LoadScene(const std::string name);
	void SaveScene(const std::string name);
	void LoadScenesFromFile();
	void SaveScenesInFile();

	void ToStringAllScenes();

private:
	// Unique instance of the time
	static std::unique_ptr<SceneManager> _instance;
	static std::once_flag onceFlag;

	std::vector<std::string> _allScene;
	Scene* currentScene;

	const std::string _fileName = "Assets/Scenes/Manager.txt";
};

