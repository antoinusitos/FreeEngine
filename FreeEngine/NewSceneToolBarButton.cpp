#include "NewSceneToolBarButton.h"
#include <iostream>
#include "Debug.h"

NewSceneToolBarButton::NewSceneToolBarButton()
{
}

NewSceneToolBarButton::~NewSceneToolBarButton()
{
}

void NewSceneToolBarButton::Execute()
{
	Debug::Instance().Log("Execute new scene button", DebugMessageType::DEBUGENGINE);
	if (_parent != nullptr)
	{
		_parent->SetActive(false);
	}
}