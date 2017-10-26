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

void Debug::Print(std::string message)
{
	std::cout << message << '\n';
	_allString.push_back(message);
	if (debugWindow != nullptr)
	{
		debugWindow->AddString(message);
	}
}

void Debug::SaveLog()
{

	std::string currentTime = Time::Instance().GetCurrentTimeAsString();

	std::string toWrite = "";

	for (std::vector<std::string>::iterator it = _allString.begin(); it != _allString.end(); ++it)
	{
		toWrite += (*it);
	}

	FileHandler::Instance().WriteFile("Assets/Log/Logs_" + currentTime + ".txt", toWrite);
	
}

void Debug::SetDebugWindow(DebugWindowLayout* newWindow)
{
	debugWindow = newWindow;
}