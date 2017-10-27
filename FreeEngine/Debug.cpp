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

void Debug::Print(std::string message, DebugMessageType messageType)
{
	std::string type = "";
	if (messageType == 0)
		type = "Log";
	else if (messageType == 1)
		type = "Warning";
	else if (messageType == 2)
		type = "Error";

	std::cout << "(" << type << ") " <<  message << '\n';

	DebugMessage dm = DebugMessage();
	dm.message = message;
	dm.messageType = messageType;

	_allString.push_back(dm);
	if (debugWindow != nullptr)
	{
		debugWindow->AddString(dm);
	}
}

void Debug::SaveLog()
{

	std::string currentTime = Time::Instance().GetCurrentTimeAsString();

	std::string toWrite = "";

	for (std::vector<DebugMessage>::iterator it = _allString.begin(); it != _allString.end(); ++it)
	{
		toWrite += (*it).message;
	}

	FileHandler::Instance().WriteFile("Assets/Log/Logs_" + currentTime + ".txt", toWrite);
	
}

void Debug::SetDebugWindow(DebugWindowLayout* newWindow)
{
	debugWindow = newWindow;
}