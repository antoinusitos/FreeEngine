#include <fstream>

#include "Debug.h"
#include "Time.h"
#include "FileHandler.h"

std::unique_ptr<Debug> Debug::_instance;
std::once_flag Debug::onceFlag;

Debug::Debug()
{
	//Print("Create Debug Class");
}

Debug::~Debug()
{
	
}

void Debug::Print(const std::string message, const DebugMessageType messageType)
{
	std::string type = "";
	std::string final = "";
	if (messageType == 0)
		type = "Log";
	else if (messageType == 1)
		type = "Warning";
	else if (messageType == 2)
		type = "Error";
	else if (messageType == 3)
		type = "Engine";

	final = "(" + type + ") " + message + '\n';
	std::cout << final;

	DebugMessage dm = DebugMessage();
	dm.message = final;
	dm.messageType = messageType;

	_allString.push_back(dm);
	if (debugWindow != nullptr)
	{
		debugWindow->AddString(dm);
	}
}

void Debug::Log(const std::string message, const DebugMessageType messageType)
{
	std::string type = "";
	std::string final = "";
	if (messageType == 0)
		type = "Log";
	else if (messageType == 1)
		type = "Warning";
	else if (messageType == 2)
		type = "Error";
	else if (messageType == 3)
		type = "Engine";

	final = "(" + type + ") " + message + '\n';
	std::cout << final;

	DebugMessage dm = DebugMessage();
	dm.message = final;
	dm.messageType = messageType;

	_allString.push_back(dm);
}

const void Debug::SaveLog()
{

	std::string currentTime = Time::Instance().GetCurrentTimeAsString();

	std::string toWrite = "";

	for (std::vector<DebugMessage>::iterator it = _allString.begin(); it != _allString.end(); ++it)
	{
		toWrite += (*it).message;
	}

	FileHandler::Instance().WriteFile("Assets/EngineLog/Logs_" + currentTime + ".txt", toWrite);
	
}

void Debug::SetDebugWindow(DebugWindowLayout* newWindow)
{
	debugWindow = newWindow;
}