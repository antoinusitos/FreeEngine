#include <fstream>

#include "Debug.h"

Debug* Debug::_instance = NULL;

Debug::Debug()
{
	Print("Create Debug Class");
}

Debug::~Debug()
{

}

void Debug::Print(std::string message)
{
	std::cout << message << std::endl;
	_allString.push_back(message);
	if (debugWindow != nullptr)
	{
		debugWindow->AddString(message);
	}
}

void Debug::SaveLog()
{
	std::ofstream myfile;
	myfile.open("Assets/Logs.txt");

	for (std::vector<std::string>::iterator it = _allString.begin(); it != _allString.end(); ++it)
	{
		myfile << (*it) << "\n";
	}

	myfile.close();
}

void Debug::SetDebugWindow(DebugWindowLayout* newWindow)
{
	debugWindow = newWindow;
}