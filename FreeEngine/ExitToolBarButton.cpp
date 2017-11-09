#include "ExitToolBarButton.h"
#include <iostream>
#include "EditorManager.h"
#include "Debug.h"

ExitToolBarButton::ExitToolBarButton()
{
}

ExitToolBarButton::~ExitToolBarButton()
{
}

void ExitToolBarButton::Execute()
{
	Debug::Instance().Log("Execute exit button", DebugMessageType::DEBUGENGINE);
	if (_parent != nullptr)
	{
		_parent->SetActive(false);
	}
	EditorManager::Instance().SetMustQuit();
}
