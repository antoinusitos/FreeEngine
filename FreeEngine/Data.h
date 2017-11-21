#pragma once

#include <string>
#include <memory>
#include <mutex>
#include <iostream>

#include "Transform.h"

class Scene;

// For release version,
// - Copy all the Assets in the Debug folder
// - Change RELEASEVERSION to true
const bool ISRELEASE = false;
const std::string DEBUGFOLDER = "FreeEngine";
const std::string RELEASEFOLDER = "Debug";
const std::string RELEASEVERSION = "0.1";

//WARNING : Be sure that objects have the correct collisions and layers
const int LAYERSNUMBER = 4; // 3 background, 2 terrain, 1 dynamic, 0 foreground

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
	DEBUGLOG,
	DEBUGWARNING,
	DEBUGERROR,
	DEBUGENGINE,
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


enum KEYCODE
{
	NONE,
	SPACE,
	ESCAPE,
	ENTER,
	ARROWUP,
	ARROWDOWN,
	ARROWRIGHT,
	ARROWLEFT,
	MOUSELEFT,
	MOUSERIGHT,
	A,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z,
	TILDE,
	F1,
	F2,
};

struct InputKey
{
	KEYCODE key;
	bool pressing = false;
	bool pressDown = false;
	bool release = false;
	bool init = false;
	bool exit = false;
};

union ConditionType
{
	bool b_return;
	float f_return;
	int i_return;
	bool t_return; //T for trigger
};

struct Condition
{
public:
	std::string name;
	int type; //0=bool, 1=int, 2=float, 3=Trigger
	ConditionType conditiontype;
};

enum EditorState
{
	EDITING,
	RUNNING,
};

union SaveData
{
	float		fValue;
	int			iValue;
	char*		sValue;
	char*		tValue;
};

struct SaveInfo
{
public:
	std::string name;
	int dataType; //0=float, 1=int, 2=char*, 3=Transform*
	SaveData data;
};

struct SceneInfo
{
public:
	std::string name;
	Scene* scene;
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

	const std::string GetProjetPath();

private:
	// Unique instance of the time
	static std::unique_ptr<Data> _instance;
	static std::once_flag onceFlag;

	std::string _projectPath = "";
	void RecoverProjetPath();
};

