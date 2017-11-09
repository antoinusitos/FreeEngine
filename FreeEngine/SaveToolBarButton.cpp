#include "SaveToolBarButton.h"
#include <iostream>
#include "Debug.h"

SaveToolBarButton::SaveToolBarButton()
{
}

SaveToolBarButton::~SaveToolBarButton()
{
}

void SaveToolBarButton::Execute()
{
	Debug::Instance().Log("Execute save button", DebugMessageType::DEBUGENGINE);
	if (_parent != nullptr)
	{
		_parent->SetActive(false);
	}
}