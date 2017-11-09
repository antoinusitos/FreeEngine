#include "MenuToolBarButton.h"
#include <iostream>

#include "SaveToolBarButton.h"
#include "NewSceneToolBarButton.h"
#include "ExitToolBarButton.h"
#include "Debug.h"

MenuToolBarButton::MenuToolBarButton()
{
	newScene = new NewSceneToolBarButton();
	newScene->InitBackground();
	newScene->SetParent(this);
	newScene->SetName("New Scene");
	_subButtons.push_back(newScene);

	save = new SaveToolBarButton();
	save->InitBackground();
	save->SetParent(this);
	save->SetName("Save");
	_subButtons.push_back(save);

	exit = new ExitToolBarButton();
	exit->InitBackground();
	exit->SetParent(this);
	exit->SetName("Exit");
	_subButtons.push_back(exit);

	SetActive(false);
}

MenuToolBarButton::~MenuToolBarButton()
{
}

void MenuToolBarButton::Execute()
{
	Debug::Instance().Log("Execute menu button", DebugMessageType::DEBUGENGINE);

	newScene->SetPosition(_position.x, _position.y + (_size.y * 1));
	newScene->SetSize(_size);

	save->SetPosition(_position.x, _position.y + (_size.y * 2));
	save->SetSize(_size);

	exit->SetPosition(_position.x, _position.y + (_size.y * 3));
	exit->SetSize(_size);

	SetActive(true);
}
