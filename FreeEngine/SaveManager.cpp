#include "SaveManager.h"
#include "Debug.h"
#include "FileHandler.h"

std::unique_ptr<SaveManager> SaveManager::_instance;
std::once_flag SaveManager::onceFlag;

SaveManager::SaveManager()
{
}

SaveManager::~SaveManager()
{
}

void SaveManager::SetFloat(const std::string name, const float value)
{
	for (std::vector<SaveInfo*>::iterator it = _allInfos.begin(); it != _allInfos.end(); ++it)
	{
		if ((*it)->name == name)
		{
			(*it)->data.fValue = value;
			return;
		}
	}
	SaveInfo* toSave = new SaveInfo();
	toSave->name = name;
	toSave->data.fValue = value;
	toSave->dataType = 0;
	_allInfos.push_back(toSave);
}

void SaveManager::SetInt(const std::string name, const int value)
{
	for (std::vector<SaveInfo*>::iterator it = _allInfos.begin(); it != _allInfos.end(); ++it)
	{
		if ((*it)->name == name)
		{
			(*it)->data.iValue = value;
			return;
		}
	}
	SaveInfo* toSave = new SaveInfo();
	toSave->name = name;
	toSave->data.iValue = value;
	toSave->dataType = 1;
	_allInfos.push_back(toSave);
}

void SaveManager::SetString(const std::string name, const std::string value)
{
	for (std::vector<SaveInfo*>::iterator it = _allInfos.begin(); it != _allInfos.end(); ++it)
	{
		if ((*it)->name == name)
		{
			int temp = value.length() + 1;
			delete (*it)->data.sValue;
			(*it)->data.sValue = new char[temp];
			strcpy_s((*it)->data.sValue, temp, value.c_str());
			return;
		}
	}
	SaveInfo* toSave = new SaveInfo();
	toSave->name = name;
	int temp = value.length() + 1;
	char* cstr = new char[temp];
	strcpy_s(cstr, temp, value.c_str());
	toSave->data.sValue = cstr;
	toSave->dataType = 2;
	_allInfos.push_back(toSave);
}

void SaveManager::SetTransform(const std::string name, Transform* value)
{
	for (std::vector<SaveInfo*>::iterator it = _allInfos.begin(); it != _allInfos.end(); ++it)
	{
		if ((*it)->name == name)
		{
			std::string s = value->ToString();
			int temp = s.length() + 1;
			delete (*it)->data.tValue;
			(*it)->data.sValue = new char[temp];
			strcpy_s((*it)->data.tValue, temp, s.c_str());
			return;
		}
	}
	SaveInfo* toSave = new SaveInfo();
	toSave->name = name;
	std::string s = value->ToString();
	int temp = s.length() + 1;
	char* cstr = new char[temp];
	strcpy_s(cstr, temp, s.c_str());
	toSave->data.tValue = cstr;
	toSave->dataType = 3;
	_allInfos.push_back(toSave);
}

const float SaveManager::GetFloat(const std::string name, bool* hasRecover)
{
	for (std::vector<SaveInfo*>::iterator it = _allInfos.begin(); it != _allInfos.end(); ++it)
	{
		if ((*it)->name == name)
		{
			*hasRecover = true;
			return (*it)->data.fValue;
		}
	}
	*hasRecover = false;
	Debug::Instance().Log("Cannot find Saved float " + name, DebugMessageType::DEBUGERROR);
	return -1;
}

const int SaveManager::GetInt(const std::string name, bool* hasRecover)
{
	for (std::vector<SaveInfo*>::iterator it = _allInfos.begin(); it != _allInfos.end(); ++it)
	{
		if ((*it)->name == name)
		{
			*hasRecover = true;
			return (*it)->data.iValue;
		}
	}
	*hasRecover = false;
	Debug::Instance().Log("Cannot find Saved int " + name, DebugMessageType::DEBUGERROR);
	return -1;
}

const std::string SaveManager::GetString(const std::string name, bool* hasRecover)
{
	for (std::vector<SaveInfo*>::iterator it = _allInfos.begin(); it != _allInfos.end(); ++it)
	{
		if ((*it)->name == name)
		{
			*hasRecover = true;
			return std::string((*it)->data.sValue);
		}
	}
	*hasRecover = false;
	Debug::Instance().Log("Cannot find Saved string " + name, DebugMessageType::DEBUGERROR);
	return "";
}

const Transform SaveManager::GetTransform(const std::string name, bool* hasRecover)
{
	for (std::vector<SaveInfo*>::iterator it = _allInfos.begin(); it != _allInfos.end(); ++it)
	{
		if ((*it)->name == name)
		{
			*hasRecover = true;
			return Transform::ReadString(std::string((*it)->data.tValue));
		}
	}
	*hasRecover = false;
	Debug::Instance().Log("Cannot find Saved Transform " + name, DebugMessageType::DEBUGERROR);
	return Transform();
}

void SaveManager::LoadAll()
{
	bool fileReadable = false;
	std::string recovered = FileHandler::Instance().ReadFile("Assets/Saves/SaveObject.txt", &fileReadable);
	if (fileReadable)
	{
		std::string delimiterEOL = "\n";
		std::string delimiterFourth = ",";
		std::string delimiterFifth = "=";


		size_t pos = 0;
		std::string token;
		while ((pos = recovered.find(delimiterEOL)) != std::string::npos) {
			token = recovered.substr(0, pos);

			// FIND TYPE

			std::string typeFull = recovered.substr(0, recovered.find(delimiterFourth));
			size_t posTemp = recovered.find(delimiterFourth);

			size_t posTempbis = typeFull.find(delimiterFifth);
			typeFull.erase(0, posTempbis + delimiterFifth.length());

			//final type
			int type = std::atoi(typeFull.c_str());

			token.erase(0, recovered.find(delimiterFourth) + delimiterFourth.length());

			// FIND NAME

			typeFull = token.substr(0, token.find(delimiterFourth));
			posTemp = token.find(delimiterFourth);

			posTempbis = typeFull.find(delimiterFifth);
			typeFull.erase(0, posTempbis + delimiterFifth.length());

			//final name
			std::string name = typeFull;

			token.erase(0, token.find(delimiterFourth) + delimiterFourth.length());

			SaveInfo* si = new SaveInfo();

			si->name = name;
			si->dataType = type;

			// FIND DATA

			if (type == 0) // float
			{
				typeFull = token.substr(0, token.find(delimiterFourth));
				posTemp = token.find(delimiterFourth);

				posTempbis = typeFull.find(delimiterFifth);
				typeFull.erase(0, posTempbis + delimiterFifth.length());

				si->data.fValue = std::atof(typeFull.c_str());
			}
			else if (type == 1) // int
			{
				typeFull = token.substr(0, token.find(delimiterFourth));
				posTemp = token.find(delimiterFourth);

				posTempbis = typeFull.find(delimiterFifth);
				typeFull.erase(0, posTempbis + delimiterFifth.length());

				si->data.iValue = std::atoi(typeFull.c_str());
			}
			else if (type == 2) // string
			{
				typeFull = token.substr(0, token.find(delimiterFourth));
				posTemp = token.find(delimiterFourth);

				posTempbis = typeFull.find(delimiterFifth);
				typeFull.erase(0, posTempbis + delimiterFifth.length());

				int temp = typeFull.length() + 1;
				si->data.sValue = new char[temp];
				strcpy_s(si->data.sValue, temp, typeFull.c_str());
			}
			else if (type == 3) // transform
			{
				typeFull = token.substr(0, token.find(delimiterFourth));
				posTemp = token.find(delimiterFourth);

				posTempbis = typeFull.find(delimiterFifth);
				typeFull.erase(0, posTempbis + delimiterFifth.length());

				int temp = typeFull.length() + 1;
				si->data.tValue = new char[temp];
				strcpy_s(si->data.tValue, temp, typeFull.c_str());
			}

			recovered.erase(0, pos + delimiterEOL.length());

			_allInfos.push_back(si);
		}
	}
	else
	{
		Debug::Instance().Print("File Assets/Saves/SaveObject.txt not readable", DebugMessageType::DEBUGERROR);
	}
}

void SaveManager::SaveAll()
{
	std::string toWrite = "";
	for (std::vector<SaveInfo*>::iterator it = _allInfos.begin(); it != _allInfos.end(); ++it)
	{
		int dt = (*it)->dataType;
		toWrite += "DataType=" + std::to_string(dt) + ',';
		toWrite += "Name=" + (*it)->name + ',';
		if (dt == 0)
		{
			toWrite += "Data=" + std::to_string((*it)->data.fValue);
		}
		else if (dt == 1)
		{
			toWrite += "Data=" + std::to_string((*it)->data.iValue);
		}
		else if (dt == 2)
		{
			toWrite += "Data=" + std::string((*it)->data.sValue);
		}
		else if (dt == 3)
		{
			toWrite += "Data=" + std::string((*it)->data.tValue);
		}

		toWrite += '\n';
	}

	std::cout << "to Write :" << '\n' << toWrite;

	FileHandler::Instance().WriteFile("Assets/Saves/SaveObject.txt", toWrite);
}