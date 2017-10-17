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
}