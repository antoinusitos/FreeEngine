#pragma once

#include <string>
#include <memory>
#include <mutex>
#include <iostream>


// For release version,
// - Copy all the Assets in the Debug folder
// - Change RELEASEVERSION to true
const bool ISRELEASE = false;
const std::string DEBUGFOLDER = "FreeEngine";
const std::string RELEASEFOLDER = "Debug";
const std::string RELEASEVERSION = "0.1";


enum ScreenType
{
	FULLSCREEN,
	WINDOWED,
};

struct EngineData
{
public:
	std::string category = "";
	std::string value = "";
};

enum DebugMessageType
{
	LOG,
	WARNING,
	ERROR,
};

struct DebugMessage
{
	std::string message;
	DebugMessageType messageType;
};

enum SoundType
{
	SOUND,
	MUSIC,
	LISTENER,
};

class Data
{
public:
	Data();
	~Data();

	// Get a unique instance of the time
	static Data& Data::Instance()
	{
		std::call_once(Data::onceFlag, []() {
			_instance.reset(new Data);
			//std::cout << "Getting  Data instance" << '\n';
		});

		return *(_instance.get());
	}

	std::string GetProjetPath();

private:
	// Unique instance of the time
	static std::unique_ptr<Data> _instance;
	static std::once_flag onceFlag;

	std::string _projectPath = "";
	void RecoverProjetPath();
};

